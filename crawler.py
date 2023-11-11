""" 
This package implements a generic crawler interface.
"""


import requests
import bs4 
from collections import deque
from collections.abc import Generator
from typing import Optional, Type
import validators
import log_utils
from dataclasses import dataclass, field
import abc
import logging
import utils




class BaseLinkCollector(abc.ABC):
    """ 
    This class is used as an interface for the link collector object.
    Even though I could implement this through an abstract method in Crawler and override it in the derived class, 
    I prefer to try this approach of composable objects.
    """
    
    @abc.abstractmethod
    def gather_links(self, content: bs4.BeautifulSoup) -> Generator[str, None, None]:
        """ 
        Given a content of a web page, gather the relevant links.
        """
        ...


class DefaultLinkCollector(BaseLinkCollector):
    def gather_links(self, content: bs4.BeautifulSoup) -> Generator[str, None, None]:
        """ 
        Gather all the links inside content.
        """
        for link in content.find_all('a'):
            ext_url: str = link.get("href")
            if ext_url is None:
                continue 
            yield ext_url



@dataclass
class BaseCrawler(abc.ABC):
    # name of the crawler
    name: str

    # the main domain of this crawler. 
    main_domain: str

    link_collector: Type[BaseLinkCollector] = field(default_factory=DefaultLinkCollector)
    
    # time between requests in seconds. 
    _time_between_requests: float = 1.0   

    # List of disallowed paths taken from robots.txt or added manually.
    disallowed_paths: set[str] = field(init=False, default_factory=set)

    # List of fetched sites to avoid repetition. This list will be added to the db.
    fetched: set[str] = field(init=False, default_factory=set)
    
    # Sites are explored in BFS order.
    queue: deque[str] = field(init=False, default_factory=deque)

    logger: logging.Logger = None

    def __post_init__(self):
        if not issubclass(self.link_collector, BaseLinkCollector):
            raise RuntimeError("Link collector must derive from BaseLinkCollector")

        self.logger = log_utils.create_logger(self.name)
        self.main_domain = self.main_domain.rstrip("/")
        self.__init_robot()
        self.queue.append(self.main_domain)

    
    @property
    def time_between_requests(self) -> float:
        return self._time_between_requests
    
    @time_between_requests.setter
    def time_between_requests(self, t: float): 
        # Time cannot be < 0.
        self._time_between_requests = t if t > 0 else 1.0


    @abc.abstractmethod
    def parse(self, content: bytes):
        """
        Parse the content of the html page.
        """
        ...


    def fetch(self) -> Optional[bs4.BeautifulSoup]:
        """
        Generator.
        Perform an http request to next site in the queue, get all the allowed links and add them to the queue.
        Return a BeautifulSoup with the content of the page or None.
        """
        # Execute the loop until the queue is empty or a valid url is found.
        while True:
            if not self.queue:
                self.logger.warning("Empty queue")
                return
       
            # TODO: check if the url popped is an url or a path in the main_domain.
            
            url = self.queue.popleft()
            self.logger.debug(f"Popped {url}")

            # The url could be a relative to the main domain so we need to check.
            if not validators.url(url):
                if utils.url_is_path(url):
                    url = self.main_domain + url
                else:
                    url = self.main_domain + "/" + url

            self.logger.debug(f"Fetching {url}")
            # check if the url is valid
            if not validators.url(url):
                self.logger.warning(f"URL not valid {url}")
                continue
           

            content = self.get_raw_content(url)
            if not content:
                self.logger.warning(f"Content not valid for {url}")
                continue
                
 
            # Parse the html and gather all the links.
            soup = bs4.BeautifulSoup(content, "html.parser")

            self.logger.debug("Extracting urls")
            for ext_url in self.link_collector.gather_links(soup): 
                if ext_url in self.fetched:
                    continue

                # self.logger.debug(f"Extracted {ext_url}")

                # TODO: This can be optimized.
                outer = False 
                for p in self.disallowed_paths:
                    if ext_url.startswith(p):
                        outer = True
                        break
                if outer:
                    continue
                
                self.fetched.add(ext_url)
                self.queue.append(ext_url)

            # ???
            return soup


    def get_raw_content(self, url: str) -> Optional[bytes]:
        """ 
        Perform an http request to url. If the response is ok return the content in bytes. 
        It is responsability of the caller to ensure that the url is a valid url. This can be done using validators.url(url).
        """
        response = requests.get(url)
        if not response:
            self.logger.warning(f"Response {response.status_code} for {url}")
            return
        return response.content
    

    def __init_robot(self):
        """ 
        Read the robots file and be sure to be conformed to the requests.
        """
        robots = self.main_domain + "/robots.txt"
        content = self.get_raw_content(robots)
        if not content:
            self.logger.warning(f"Error while reading robots.txt")
            return

        # The robots file uses utf-8.
        content = content.decode("utf-8")

        # Start parsing. Search for the user-agent: * 

        idx = content.find("User-agent: *")
        if idx == -1:
            self.logger.warning("No found user agent *.")
            return
        
        lines = content[idx:].splitlines()
        for line in lines[1:]: # drop the first line of user agent
            # ignore comments.
            if line.startswith("#"):
                continue 
            
            if line.startswith("Allow"):
                ...
            elif line.startswith("Disallow"):
                path = line[line.find(":") + 1 :].strip().replace("\n", "")
                self.disallowed_paths.add(path)



""" 
Implementation of a crawler for the http://books.toscrape.com/index.html learning site.
This crawler gather all the info about all the books registered. These info will be processed and saved in a database
to be used by the search engine.

TODO: this can be done in parallel.
"""

from dataclasses import dataclass
from typing import Optional
import requests
import bs4
import log_utils
import logging 
from collections.abc import Generator

@dataclass
class BookInfo:
    title: str
    description: str
    # price: str 


@dataclass
class BookCrawler:
    domain: str = "http://books.toscrape.com"
    logger: logging.Logger = log_utils.create_logger("BookCrawler")


    def fetch(self) -> Generator[BookInfo, None, None]:
        """
        Read all the 50 pages of the catalogue and extract the 20 books per page.
        """
        for page in range(1, 51):
            # Current page in the catalogue
            url = self.domain + f"/catalogue/page-{page}.html" 
            content = self.get_content(url)
            if content is None:
                continue 

            soup = bs4.BeautifulSoup(content, "html.parser")
            # Books in the current page
            books = soup.find_all("article", class_="product_pod")
            for book in books:
                # Now read the content page of the book and gather the main info
                book_url = book.find("a")["href"]
                book_url = self.domain + "/catalogue/" + book_url

                book_content = self.get_content(book_url)
                if book_content is None:
                    continue
                book_soup = bs4.BeautifulSoup(book_content, "html.parser")
                title = book_soup.find("h1").text
                description = book_soup.find("article", class_="product_page").find("p").text

                yield BookInfo(title, description)


    def get_content(self, url: str) -> Optional[bytes]:
        response = requests.get(url)
        if not response:
            self.logger.warning(f"Response {response.status_code} for {url}")
            return
        return response.content
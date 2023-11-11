import bs4 


class TextExtractor:
    """ 
    Take an html page and extract all the text paragraphs.
    """
    

    def __call__(self, content: bytes) -> list[str]:
        """ 
        Return a list of the paragraphs.
        """
        soup = bs4.BeautifulSoup(content, "html.parser")
        
        # # kill all script and style elements
        # for script in soup(["script", "style"]):
        #     script.extract()    # rip it out

        texts = []
        for p in soup.find_all("p"):
            texts.append(p.get_text())

        return texts
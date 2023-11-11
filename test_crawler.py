import bs4
import time
from book_crawler import BookCrawler, BookInfo



def test():
    crawler = BookCrawler()

    infos = crawler.fetch()

    for info in infos:
        print(f"Title: {info.title}\n{info.description}")
        break


if __name__ == "__main__":
    test()
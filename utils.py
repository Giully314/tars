


def url_is_image(url: str) -> bool:
    return url.endswith("png") or url.endswith("jpg") or url.endswith("jpeg")

def url_is_wiki_file(url: str) -> bool:
    """
    Check if an url or path contains the "File:" substring (for wikipedia only).
    """
    return "File:" in url

def url_is_query_or_section(url: str) -> bool:
    """
    Check if an url or path contains the '#' (section) or '?' (query).
    """
    for c in url:
        if c == '#' or c == '?':
            return True
    return False


def url_is_wiki_info(url: str) -> bool:
    """
    Check if an url or path contains the "Wikipedia:" substring (for wikipedia only).
    """
    return "Wikipedia:" in url


def url_is_path(url: str) -> bool:
    """ 
    Check if url is a path of a domain: for example while scraping a page there could be links relative to the 
    main domain defined as /path/to/something.html
    TODO: The check is not complete
    """
    return url.startswith("/")
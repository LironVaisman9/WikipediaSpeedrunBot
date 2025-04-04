import requests
from requests.utils import quote


WIKIPEDIA_URL = "http://en.wikipedia.org/wiki/"

BANNED = ['Main_Page', 'Wikipedia:', 'Special:', 'Talk:', 'Portal:', 'Help:', 'Template:',
          'Template_talk:', 'File:', 'File_talk:', 'MediaWiki:', 'MediaWiki_talk:', 'Category:',
          'Category_talk:', 'Draft:', 'Draft_talk:', 'TimedText:', 'TimedText_talk:', 'Module:',
          'Module_talk:', 'User:', 'User_talk:', 'Book:', 'Book_talk:', 'Education_Program:',
          'Education_Program_talk:', 'Gadget:', 'Gadget_talk:', 'Gadget_definition:',
          'Gadget_definition_talk:', 'Topic:', 'Topic_talk:']

"""
Checks if a wiki page exists 
@param page_name the name of the wiki page
@return true if the page exists and false if not
"""
def pageExists(page_name: str) -> bool:
    
    encoded_page_name = quote(page_name)
    response = requests.get(WIKIPEDIA_URL + encoded_page_name)
    return response.status_code == 200
"""
Checks if a wiki page is valid 
@param page_name the name of the wiki page
@return true if the page is valid and false if not
"""
def pageValid(page_name: str) -> bool:
    if not page_name:
        return False
    if not pageExists(page_name):
        return False
    for banned_string in BANNED:
        if page_name.startswith(banned_string):
            return False
    return True
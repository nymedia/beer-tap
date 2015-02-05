import requests

class User(object):

  def __init__(self, uid):
    return self.__load__(uid)

  def __load__(self, uid):
    # Load data from sqlite database
    r = requests.get('/node/' + uid)

    # check if loaded correctly
    if (r.status_code == 204):
      return True
    else:
      return False

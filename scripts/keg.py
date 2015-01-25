class Keg(object):

  def __init__(self, kid):
    return self.__load__(kid)

  def __load__(self, kid):
    # Load data from sqlite database
    r = requests.get('/node/' + kid)

    # check if loaded correctly
    if (r.status_code == 204):
      self.keg = r.text
      return TRUE
    else
      return FALSE

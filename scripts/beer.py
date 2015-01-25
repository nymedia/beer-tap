class Beer(object):
  def __init__(self, bid):
    return self.__load__(kid)

  def __load__(self, bid):
    # Load data from sqlite database
    db.execute("SELECT * FROM beer WHERE bid = '%d'" % bid)
    val = db.fetchone();
    self.BID = val.bid;
    self.User

    # check if loaded correctly
    try:
      self.BID
    except NameError:
      return FALSE
    else:
      return TRUE

  def __save__(self):
    # Store data in database
    return TRUE

  def __pour__(self):
    # open valve and bump timer.
    return TRUE

  def __create__(keg, user):
    db.execute("INSERT INTO beer VALUES (NULL, ?, ?)", (keg.kid, user.uid))

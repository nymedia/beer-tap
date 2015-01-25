class User(object):

  db = None

  def __init__(self, bid):
    return self.__load__(kid)

  def __load__(self, bid):
    # Load data from sqlite database
    self.db.execute("SELECT * FROM user WHERE uid = '%d'" % uid)
    val = db.fetchone();
    self.UID = val.uid;
    self.name = val.name;
    self.card_id = val.card_id;

    # check if loaded correctly
    try:
      self.UID
    except NameError:
      return FALSE
    else:
      return TRUE

  def __save__(self):
    # Store data in database
    self.db.execute("UPDATE user SET name=?, card_id=? WHERE uid=?", (self.name, self.card_id, self.uid))
    return TRUE

  def __pour__(self):
    # open valve and bump timer.
    return TRUE

  @staticmethod
  def create(name, card_id):
    db.execute("INSERT INTO user VALUES (NULL, ?, ?)", (name, card_id))

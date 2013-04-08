echo import DatebaseName SQLFile

mysql --host=localhost --user=root --password=root --port=3306 --default-character-set=utf8 --database=%1 --comments < %2
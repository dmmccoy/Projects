
SELECT * FROM Books WHERE isbn_13 IN(SELECT DISTINCT isbn_13 FROM book_tags)
;




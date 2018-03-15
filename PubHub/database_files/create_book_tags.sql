-- Table: public.book_tags

-- DROP TABLE if exists public.book_tags;

CREATE TABLE book_tags
(
	isbn_13 varchar (13),
	tag_name varchar,
	primary key(isbn_13, tag_name),
	foreign key(isbn_13) references books(isbn_13)
)



WITH (
    OIDS = FALSE
)
TABLESPACE pg_default;

ALTER TABLE public.book_tags
    OWNER to postgres;
	
insert into book_tags values(
	'1111111111111',
	'awesome'
);


DROP TABLE IF EXISTS users;

CREATE TYPE confirm_method_t AS ENUM ('phone', 'email');

CREATE TABLE users (
	user_id serial,
	email varchar(60) UNIQUE,
	phone varchar(60) UNIQUE,
	confirm_method confirm_method_t NOT NULL,
	username varchar(60) NOT NULL,
	password varchar(100) NOT NULL,

	CONSTRAINT pk_users_user_id PRIMARY KEY (user_id)
);

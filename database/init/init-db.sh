#!/bin/bash
set -e

psql -v ON_ERROR_STOP=1 --username "$POSTGRES_USER" --dbname "$POSTGRES_DB" <<-EOSQL
	CREATE TABLE tests(name VARCHAR(48) NOT NULL, timestamp INTEGER NOT NULL, result BOOLEAN NOT NULL);
EOSQL

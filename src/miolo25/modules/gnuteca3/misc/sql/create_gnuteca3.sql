
\echo "Voce precisa entrar no diret�rio onde os arquivos .sql est�o!"

\c template1
\echo \n
\echo "Criando Base Gnuteca3"
CREATE DATABASE gnuteca3 WITH TEMPLATE = template1 ENCODING = 'UTF8';

ALTER DATABASE gnuteca3 OWNER TO postgres;

\echo "Conectando na base Gnuteca3";
\connect gnuteca3

\i dump_gnuteca3.sql

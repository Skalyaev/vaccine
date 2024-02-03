# Vaccine

*SQL Injection*

We all know how important secure programming is. In this case you will try to find filtering errors in the data input. SQL Injection is the injection of SQL commands to alter the behaviour of a program and execute commands on the database.
In this project you will create a tool that is able to detect SQL injections providing a URL.

## Checklist
- MySQL
    * [x] Stacked queries
    * [x] Union-based
    * [x] Error-based
    * [x] Blind-based
- Microsoft SQL Server
    * [x] Union-based
    * [x] Error-based
    * [x] Blind-based
- PostgreSQL
    * [x] Union-based
    * [x] Error-based
    * [x] Blind-based
- SQLite
    * [x] Union-based
    * [x] Blind-based

## Usage
```sh
sudo apt update
sudo apt install git make docker.io libcurl4-openssl-dev libjsoncpp-dev
git clone git@github.com:Skalyaeve/vaccine.git
cd vaccine
make
sudo make docker # this will be very long
```
> Open another terminal
```sh
./Vaccine -d mysql http://localhost:4242
less archive.json
```
```sh
rm archive.json
./Vaccine -d postgresql http://localhost:4343
less archive.json
```
```sh
rm archive.json
./Vaccine -d sqlite http://localhost:4444
less archive.json
```
```sh
rm archive.json
./Vaccine -d microsoftsql http://localhost:4545
less archive.json
```
```sh
sudo make docker-stop
sudo make docker-fclean
make fclean
```

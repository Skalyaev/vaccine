# <p align="center">vaccine</p>

> _Projet d'introduction à la compréhension d'une faille web très connue, la fameuse injection SQL (SQLi). Vous devrez créer un outil pour automatiser vos actions._
>
> _Nous savons tous combien un développement sécurisé est important. Dans ce contexte, vous essaierez de trouver des erreurs de filtrage dans les entrées de données. L'injection SQL consiste à injecter des commandes SQL pour modifier le comportement d'un programme et exécuter des commandes sur la base de données._
>
> _Dans ce projet, vous allez créer un outil capable de détecter les injections SQL à partir d'une URL._

## Checklist

- MySQL
  - [x] Stacked
  - [x] Union
  - [x] Error
  - [x] Blind
- Microsoft SQL Server
  - [x] ~~Stacked~~
  - [x] Union
  - [x] Error
  - [x] Blind
- PostgreSQL
  - [x] ~~Stacked~~
  - [x] Union
  - [x] Error
  - [x] Blind
- SQLite
  - [x] ~~Stacked~~
  - [x] Union
  - [x] ~~Error~~
  - [x] Blind

## Install

```bash
sudo apt update -y
sudo apt install -y docker.io
```

```bash
git clone https://github.com/Skalyaeve/vaccine.git
cd vaccine
# run les conteneurs test:
sudo make docker # ça va être plutôt long
```

## Usage

```bash
sudo docker exec -it code bash
```

```bash
./Vaccine -t mysql http://nginx:4646
less archive.json
```

```bash
rm archive.json
./Vaccine -t postgresql http://nginx:4343
less archive.json
```

```bash
rm archive.json
./Vaccine -t sqlite http://nginx:4444
less archive.json
```

```bash
rm archive.json
./Vaccine -t microsoftsql http://nginx:4545
less archive.json
```

```bash
sudo make docker-stop
sudo make docker-fclean
```

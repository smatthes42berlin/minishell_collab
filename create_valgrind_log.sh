#!/bin/bash

# Der Name des Ordners, in dem die Logs gespeichert werden sollen.
LOG_DIR="valgrind_logs"

# Das zu startende Programm (ersetzen Sie ./deinProgramm mit dem tatsächlichen Pfad zu Ihrem Programm).
PROGRAM="./minishell"

# Überprüfen, ob der Log-Ordner existiert. Wenn ja, leere ihn. Wenn nein, erstelle ihn.
if [ -d "$LOG_DIR" ]; then
    echo "Leere vorhandenen Log-Ordner: $LOG_DIR"
    rm -rf "$LOG_DIR"/*
else
    echo "Erstelle Log-Ordner: $LOG_DIR"
    mkdir "$LOG_DIR"
fi

# Starte das Programm mit Valgrind und lege die Logs im spezifizierten Ordner ab.
valgrind --leak-check=full --show-leak-kinds=all --log-file="$LOG_DIR/valgrind-%p.log" $PROGRAM

echo "Valgrind-Logs wurden in $LOG_DIR gespeichert."

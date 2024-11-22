#!/bin/bash

# Configurations
REPO_PATH="C:\Users\MSI\Documents\iatic3\unix\TOI24-master\C2-Git\TP2\ATOI_24_TP_GIT"        # Chemin du dépôt local
BACKUP_PATH="C:\Users\MSI\Documents\iatic3\unix\TOI24-master\C2-Git\TP2\ATOI_24_TP_GIT\backup"     # Chemin de sauvegarde (disque dur ou cloud)
REMOTE_URL="https://github.com/AguirChams/remote_repositorie_TP2.git" # URL du dépôt distant
BACKUP_DATE=$(date +"%Y-%m-%d_%H-%M-%S")   # Date pour nommer les backups

# Vérifications préliminaires
if [ ! -d "$REPO_PATH/.git" ]; then
  echo "Erreur : Le chemin spécifié n'est pas un dépôt Git valide."
  exit 1
fi

# Étape 1: Synchroniser le dépôt local avec le dépôt distant
echo "Synchronisation du dépôt local avec le dépôt distant..."
cd "$REPO_PATH"
git remote -v || git remote add origin "$REMOTE_URL"

# Pousse toutes les branches et les tags
git push --all origin
git push --tags

# Étape 2: Sauvegarder le dépôt local
echo "Création d'une sauvegarde du dépôt local..."
BACKUP_REPO_PATH="${BACKUP_PATH}/repo_backup_${BACKUP_DATE}"
mkdir -p "$BACKUP_REPO_PATH"
cp -r "$REPO_PATH" "$BACKUP_REPO_PATH"

echo "Sauvegarde effectuée dans : $BACKUP_REPO_PATH"

# Étape 3: Sauvegarde du reflog (optionnel)
echo "Sauvegarde des reflogs..."
git reflog > "${BACKUP_REPO_PATH}/reflog_backup_${BACKUP_DATE}.txt"
echo "Reflog sauvegardé dans ${BACKUP_REPO_PATH}"

# Étape 4: Clone une copie ailleurs
CLONE_PATH="${BACKUP_PATH}/cloned_repo_${BACKUP_DATE}"
echo "Clonage du dépôt vers : $CLONE_PATH"
git clone "$REMOTE_URL" "$CLONE_PATH"

# Résumé
echo "Sauvegarde terminée avec succès !"
echo "Dépôt synchronisé avec le dépôt distant."
echo "Dépôt cloné dans : $CLONE_PATH"
echo "Backup local disponible dans : $BACKUP_REPO_PATH"

# Grimoire — contexte pour Claude

## Qui travaille ici
- **Manal** : directrice artistique et UX/UI designer, cheffe de projet de Grimoire. **Débutante totale dans Unreal** (première ouverture le 26/11/2026). Elle connaît très bien Figma.
- Parle-lui **toujours en français**, simplement, étape par étape, avec des analogies Figma quand c'est utile (Concepteur = Design, Graphique = Prototype, Hiérarchie = Calques, Blueprint parent = composant principal).
- Le freelance (Leo) continue de travailler sur le gameplay. **Manal s'occupe de l'UI** : HUD en jeu, page du Grimoire, menus. Avant de modifier un fichier partagé (`CW_PlayerHUD`, Blueprints de gameplay), rappelle-lui de vérifier avec Leo : les `.uasset` ne se fusionnent pas dans Git.

## Le jeu
Grimoire : mélange de TFT (auto-battler) et de Slay the Spire, avec gacha. 3 factions jouables :
- Égyptiens : Disciple, Kepesh, Priestess, Shardanes
- Romains : Legionnaire, Praetorian, Sagittarius, Scorpion
- Vikings : Frostwolf, Huskarl, Outfielder, Runeweaver

3 ennemis (Enemy1 à 3). Système de vagues, grille de placement hexagonale, synergies, invocation contre une monnaie.

## Environnement
- Projet : `D:\DEV\Grimoire---DEV`, dépôt GitHub `Tomateau1/Grimoire---DEV`, **branche de travail `test_manel`** (ne jamais travailler sur `main`).
- Unreal Engine **5.8.4** dans `D:\UE_5.8`. Visual Studio Community 2026. Projet C++ (module `Grimoire`), mais quasiment toute la logique est en Blueprints.
- Wwise 2025.1.12 dans `D:\Wwise2025.1.12.9287` (audio). Le projet de sons Wwise (`D:\DEV\Wwise\Grimoire\Grimoire_WwiseProject.wproj` + GeneratedSoundBanks) **n'est pas encore récupéré** : le jeu est muet dans l'éditeur, c'est normal. Ne pas modifier `WwiseProjectPath` dans `Config/DefaultGame.ini`.
- Plugin `FlatNodes` désactivé dans `Grimoire.uproject` (cosmétique, absent de l'installation).
- Lancer le jeu : ouvrir la map `Content/Maps/MainMenu`, puis Play. La partie se joue dans `TestMap`.

## Règles Git
- **Toujours faire un commit avant de laisser une IA modifier le projet**, pour pouvoir revenir en arrière.
- Ne **jamais** committer : `Plugins/WwiseSoundEngine/ThirdParty/**` (gros binaires, déjà ignorés), `Plugins/Wwise/LauncherInfo.json`, le dossier `Grimoire---DEV_WwiseProject/`.
- Manal utilise GitHub Desktop.

## Où sont les choses
- UI : `Content/Core/UI` (widgets `CW_*` = CommonUI activables, `W_*` = sous-widgets). HUD en jeu : `CW_PlayerHUD`. Panneau unités/équipement : `CW_Inventory`. Les écrans s'ouvrent avec **Push Game Stack** (cible : Get CWMain Stack).
- Données : `Content/Core/Common/DataTables` (DT_UnitsData, DT_FactionsData, DT_ClassesData, DT_SynergyBonuses), `StringTables` (ST_UnitsInformation, ST_FactionsInformation…), `DataAssets` (DA_Unit_*, DA_Enemy_*).
- États du joueur : `Content/Core/Player/States/BPC_PlayerState_*` (interface OnEnter / OnExit / OnTick). Quand on surcharge OnEnter/OnExit dans un enfant, **appeler d'abord la fonction parente**.
- Polices : Cormorant Upright et Grenze Gotisch (`Content/Fonts`).
- C++ : `Source/Grimoire` (DataAssets UUnitData/UEnemyData/UPlayerData/UProjectileData, helpers de sauvegarde `MTCodeHelpers`).

## Fait le 26/11/2026
- Bouton **casque** (`ButtonHelmet`, texture `T_Icon_Helmet`) ajouté dans `CW_PlayerHUD` : ouvre Unités / Équipement, avec sa propre animation `AButtonHelmetClicked`.
- Bouton **grimoire** (variable encore nommée `ButtonInventory`) : ouvre maintenant le widget **`CW_Grimoire`** (parent `CW_BaseActivatableWidget`), pour l'instant un Overlay + une Image provisoire.
- Case **Sell** (`BP_Tile_SellUnit`, dans TestMap) déplacée, et visible uniquement pendant qu'on déplace une unité (cachée par défaut, affichée dans OnEnter de `BPC_PlayerState_PlacingUnit`, recachée dans OnExit de PlacingUnit et OnEnter de `BPC_PlayerState_Idle`).

## Objectif en cours : la page du Grimoire, fidèle au Figma
Figma : fichier `fPGNLq2YnAywnfJaKdlida`, page « desktop » (maquettes en 1920×1080).
- Écran **« faction »** (node `534:6818`) : livre ouvert ; à gauche des onglets Romains (rouge), Égyptiens (noir), Vikings (bleu) + Boutique ; page gauche = grille de cartes d'unités avec étoiles (cartes sombres = pas encore obtenues, à confirmer) ; page droite = nom et texte de la faction + bonus de faction.
- Écran **« Template unité »** (node `541:20956`) : fiche d'une unité (grande illustration, étoiles, barres PV, histoire, passif, sort, bonus de faction).
- HUD (« Placement » `534:6493` / `571:39151`, « 1 » `469:1076`), menu principal (« 3 » `571:38945`), réglages en livre (« 11 » `575:28440`), boutique (`541:21364`), recettes (`541:30212`), inscriptions (`550:38208`).

Images de l'écran « faction » déjà exportées du Figma (28/11/2026) dans `ArtSource/UI/Grimoire` (ignoré par Git) : livre, onglets, logos, ornements, séparateur, étoile, croix, bouton boutique. Les fichiers `_ref_*` sont des captures de référence, à ne pas importer. Destination prévue dans Unreal : `/Game/Assets/UI/Textures/Grimoire`. Le compte Figma est en plan Starter : peu d'appels MCP Figma disponibles, les économiser.

Reste à faire pour le Grimoire, dans l'ordre :
1. Bouton de fermeture (croix) dans `CW_Grimoire` + à la fermeture, réafficher les boutons Fight, grimoire et casque (voir comment `CW_Inventory` le fait). Masquer aussi le casque quand un panneau est ouvert.
2. Fond du livre et onglets de factions d'après le Figma.
3. Page faction remplie depuis DT_UnitsData / DT_FactionsData / string tables.
4. Fiche unité.
5. Renommer `ButtonInventory` en `ButtonGrimoire`.

## Bugs connus (pas la priorité de Manal)
- Crash à la fin de la vague 10.
- Plus de 200 000 avertissements « Divide by zero » par partie dans `ABP_Enemy1` / `ABP_Enemy2`, et des Print String de debug en continu (BP_GameMode, états) : journal de 200 Mo+.
- La 2e unité vendue rapporte 0 cendre.
- Unités en double dans l'inventaire.

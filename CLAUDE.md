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

Images de l'écran « faction » déjà exportées du Figma (28/11/2026) dans `ArtSource/UI/Grimoire` (ignoré par Git) : livre, onglets, logos, ornements, séparateur, étoile, croix, bouton boutique. Les fichiers `_ref_*` sont des captures de référence, à ne pas importer. **Attention aux exports Figma** : 4 images (Icon_Close, ShopButton_Frame, Tab_Romans, Star) avaient un fond gris opaque (245,245,245) + l'ombre portée cuite dedans → cadre gris visible en jeu. Corrigé le 28/11/2026 (fond rendu transparent, ombre convertie en noir semi-transparent ; originaux gardés en `_orig_*.png`). Vérifier la transparence de tout nouvel export (fond du frame Figma à décocher). Destination prévue dans Unreal : `/Game/Assets/UI/Textures/Grimoire`. Le compte Figma est en plan Starter : peu d'appels MCP Figma disponibles, les économiser.

**Fait le 28/11/2026** : les 13 textures sont importées dans `/Game/Assets/UI/Textures/Grimoire` (réglées pour l'UI : pas de mipmaps, compression UserInterface2D). `CW_Grimoire` est construit en statique : `BackgroundDim` + `FrameScale` (ScaleBox) > `Frame1920x1080` (SizeBox) > `Canvas` → les positions du Canvas sont **les coordonnées Figma** en 1920×1080. Contient : onglets `TabRomans/TabEgyptians/TabVikings` (+ logos), `BookBackground`, `ButtonShop`, `UnitGrid` (UniformGridPanel vide, page gauche), `RightPage` (titre, `FactionDescription`, séparateur, `BonusList`), `ButtonClose`. Textes = Lorem provisoire. Aucune logique Blueprint encore branchée (les boutons ne font rien).

Reste à faire pour le Grimoire, dans l'ordre :
1. ~~Bouton de fermeture~~ **Fait le 28/11/2026** : fonction `CloseGrimoire` dans `CW_Grimoire` (appelée par OnClicked de `ButtonClose`) ; `HideHelmetButton`/`ShowHelmetButton` ajoutées dans `CW_PlayerHUD` (casque caché à l'ouverture du Grimoire et de l'Inventaire) ; `CW_Inventory` réaffiche le casque et le remet en IsActive=false à la fermeture. Échap : **fait le 28/11/2026** via une surcharge `OnKeyDown` dans `CW_Grimoire` (si touche = Escape → CloseGrimoire, réponse Handled, sinon Unhandled, via variable locale `Reply`) ; `bIsFocusable = true`, pas de widget de focus désigné : `ButtonClose` (CommonButton) ne prend pas le focus, il provoquait un warning. Le Grimoire prend donc le focus lui-même. Pas d'action « retour » CommonUI configurée dans le projet (`BP_InputData` vide). À tester en jeu.
2. ~~Fond du livre et onglets~~ **Fait le 28/11/2026** : halo de sélection `TabGlow` (texture `T_Grimoire_Tab_Glow` générée : halo blanc doux seul, sans trait dur, profil copié de l'export Vikings ; Canvas 5,64 272×131) déplacé par RenderTranslation (Y +107 px par onglet). Les 3 onglets sont recalés pour que leur bande visible fasse exactement 222×81 à x=30 (y = 89 / 196 / 303) ; bande Vikings sans halo `T_Grimoire_Tab_Vikings_Band`. Variable `SelectedFaction` (type **Name** = nom de ligne de DT_FactionsData : Romans / Egyptians / Vikings ; l'outil IA ne sait pas créer de variable enum). Fonction `SelectFaction(Faction)` : halo + titre + logo (titres encore écrits en dur, à remplacer à l'étape 3). Romains sélectionnés à l'ouverture (BP_OnActivated). Pas d'effet de survol sur les onglets.
3. ~~Page faction remplie~~ **Fait le 28/11/2026** (version statique par faction, pas générée depuis DT_UnitsData) :
   - String table **`ST_Grimoire`** (`Content/Core/Common/StringTables`), en français : clés `<Faction>Title`, `<Faction>Description`, `<Faction>BonusIntro`, `<Faction>Bonus1..4` (Faction = Romans / Egyptians / Vikings) + `ComingSoon` (« À venir »). Textes et paliers repris du Notion (pages Empire Romain / Égypte Antique / Viking et « Bonus de Factions et de classes ») et des valeurs de DT_SynergyBonuses (paliers 2/4/6/8 du jeu, le Notion a d'autres paliers pour les Égyptiens).
   - Cartes importées dans `/Game/Assets/UI/Textures/Grimoire/Cards` (`T_Card_Legionnaire/Sagittarius/Disciple/Kepesh/Huskarl/Outfielder`, 1080 px de haut). **Supposition à confirmer** : carte « drengr » = Huskarl, « lanceur de hache » = Outfielder.
   - `UnitPages` (WidgetSwitcher, Canvas 403,225 497×619) contient `UnitGridRomans/Egyptians/Vikings` (UniformGridPanel 2×2) : ligne 1 = communes (carte + 1 étoile), ligne 2 = rares (fond sombre + logo de faction pâle + « À venir », 2 étoiles). Cartes 135×250 (Égyptiens 148×250). Widgets nommés `Card<Unit>`, `CardArt<Unit>` / `CardBack/CardLogo/CardSoon<Unit>`, `CardStars<Unit>`. Quand une carte rare arrive : remplacer le fond sombre par un `CardArt`.
   - `SelectFaction` : `UnitPages.SetActiveWidgetIndex` (0/1/2) puis Title/Description/BonusIntro/Bonus1..4 via `MakeTextFromStringTable(ST_Grimoire, ToString(Faction)+suffixe)`. Ajout de `BonusIntro` et `Bonus4` dans la page droite (retour à la ligne auto).
   - Les héros ne sont pas dans la démo : ignorés. Unités Épiques du Notion (Vestales, Centurion…) pas intégrées au jeu : ignorées.
4. Fiche unité : **première version faite le 28/11/2026**, à tester en jeu.
   - Images exportées par Manal (`D:\ASSETS UI\Page unité`), copiées dans `ArtSource/UI/Grimoire/UnitSheet` et importées dans `/Game/Assets/UI/Textures/Grimoire/UnitSheet` : `T_Grimoire_Sheet_Star` (étoile sombre), `Sheet_Bullet` (puce), `Sheet_Separator`, `Ornament_TopRight/BottomLeft`, `Icon_Back`, `Illu_Placeholder` (Birka). La référence est `_ref_FicheUnite.png` (3840×2160 = 2× Figma).
   - Dans `CW_Grimoire` : Canvas `UnitSheet` (caché par défaut), contenant :
     - `SheetIllustration` dans un ScaleBox, zone 275,88 781×903 ;
     - les ornements et le bouton `SheetBack` (flèche ←) ;
     - `SheetRightPage` en 1094,140 703×830 : logo, nom, 3 étoiles (2 et 3 cachées), histoire, passif, sort, 2 séparateurs, bonus de faction.
   - Les 6 cartes communes sont enveloppées dans des Buttons `CardButton<Unit>` sans style. OnClicked appelle **`ShowUnit(Unit, Art)`** : la carte sert d'illustration, les textes viennent des clés `<Unit>Name/Story/Passive/Spell` de ST_Grimoire, puis la fiche est montrée et la grille et la page droite sont cachées. **`HideUnitSheet`** fait l'inverse. Elle est appelée par `SheetBack` et à la fin de `SelectFaction`, qui met aussi à jour `SheetLogo` et `SheetBonus1..4`.
   - Textes des unités encore provisoires (« à compléter »). Noms FR : Légionnaire, Sagittaire, Disciple de Râ, Guerrier Kepesh, Drengr (= Huskarl), Lanceur de hache. Les rares (« À venir ») ne sont pas cliquables. Pas encore de vraie illustration par unité : on affiche la carte.
5. Renommer `ButtonInventory` en `ButtonGrimoire` : **en attente de Leo**, la variable est aussi utilisée dans `BP_PlayerCharacter` (Blueprint de gameplay de Leo) et `CW_Inventory`. Le renommage modifierait ces fichiers.

Figma : le quota MCP du plan Starter a été **atteint le 28/11/2026**. Pour la fiche unité, Manal exporte elle-même la capture et les images dans `ArtSource/UI/Grimoire/UnitSheet`.

## Bugs connus (pas la priorité de Manal)
- Crash à la fin de la vague 10.
- Plus de 200 000 avertissements « Divide by zero » par partie dans `ABP_Enemy1` / `ABP_Enemy2`, et des Print String de debug en continu (BP_GameMode, états) : journal de 200 Mo+.
- La 2e unité vendue rapporte 0 cendre.
- Unités en double dans l'inventaire.
- Dans `TestMap_Units` (pas de `BP_Tile_SellUnit`), erreur « Accès à Aucun » sur Set Actor Hidden In Game dans `BPC_PlayerState_Idle` (et `PlacingUnit`) : il manque un Is Valid après Get Actor Of Class. Correction prévue, à valider avec Leo (Blueprints de gameplay partagés).

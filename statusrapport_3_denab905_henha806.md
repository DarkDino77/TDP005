# Statusrapport 2
## Vad som arbetats med
- Vi har implementerat färdigt alla ska-krav, inklusive D2.
- Vi har även hunnit implementera en mängd alla bör krav under vecka 49, exklusive A8 och F5.

## Vad som ska arbetas med
Denna vecka ska dokument skrivas, programmet testas samt redovisas. Idag på måndag ska kodgranskningsprotokollet vara färdigställt och inskickat. Under tisdag-onsdag ska designspecifikationen skrivas om samt dokumenteringen av koden ska ske. Torsdag-Fredag Ska individuell reflektionsdokument skrivas samt det individuella protfolio-inlägget publiceras. Under fredagen ska även projektet presenteras, inför det bör vi rimligen gått igenom koden en sista gång.

## Backlog
Följande krav i backloggen är sorterad i prioritet för varje vecka.
### Vecka 48
- A1 - Det ska finnas en spelarkaraktär
- D1 - Spelplanen ska representeras av applikationsfönstret och ska även begränsas av denna.
- F1 - Spelplanen ska vara sedd rakt ovanifrån med ett isometriskt perspektiv.
- A6 - Spelarkarakträren ska rikta sig mot muspekaren.
- A16 - Spelaren ska kunna förflytta sig på spelplanen enligt tabell 1.
- B1 - Fiender ska kunna ”spawna” på spelplanen längs planens höger- och vänstersidor.
- B3 - Fiender ska ”spawna” baserat på tid från start, där första våg av fiender ”spawnar” vid tid 0.
- B4 - Fiender ska kunna röra sig på spelplanen

### Vecka 49
- A17 - Spelaren ska börja med ett vapen enligt tabell 2.
- A13 - Spelarens första vapen ska ha oändligt med ammunition.
- A7 - Spelarkaraktären ska skjuta ett skott i dess nuvarande riktning när användaren trycker på vänster musknapp.
- A14 - När spelaren skjuter ska ett skott ”spawna” framför spelaren som har samma riktning som spelaren hade då den sköts och ha en bestämd konstant hastighet.
- A15 - Spelaren ska inte kunna röra sig utanför spelplanen.
- A12 - När spelarens hälsa når 0, ska spelet avslutas.
- B8 - När en fiendes hälsa når 0, ska fienden försvinna från spelplanen.
- B11 - Det ska finnas två typer av fiender med olika egenskaper enligt tabell 5.
- C1 - När ett skott kolliderar med ett föremål ska skottet försvinna.
- C2 - När ett skott kolliderar med en fiende ska fienden ta skada
- C3 - När en karaktär kolliderar med ett objekt (Statiska föremål, förstörbara föremål samt andra
karaktärer) så hindras den från att gå vidare i den relevanta riktningen.
- C4 - När en fiende kolliderar med spelaren ska spelaren ta lika stor skada som fienden har som
närstridsskada.
- F2 - All grafik ska vara två-dimensionella sprites.
- D2 - När spelplanen laddas in bör en kombination av statiska och förstörbara föremål laddas in på kartan på bestämt mönster.

- D3 - Spelplanen bör ha en bakgrundstextur som består av upprepade sprites. *
- B5 - Fiender bör röra sig i en rak linje mot spelaren. *
- B7 - Fiender bör försöka ta sönder föremål på kartan som inte är statiska och som fienden kolliderar
med på den raka vägen mot spelaren.
- B9 - Det bör finnas fler typer av fiender som alla har olika egenskaper, såsom vapen, olika mycket
hälsa, hastighet samt olika utseenden. *
- B10 - När en fiende dör bör det finnas en chans att föremål som är relevanta för den nuvarande
spelarnivån läggas ner på marken där fienden dog.
- A8 - Spelaren ska bläddra igenom sina vapen när användaren scrollar med mushjulet.
- A18 - Spelaren ska kunna bli tilldelad fler vapen när spelaren uppnåt den relevanta spelarnivån som
ges av tabell 2.
- C6 - Fienden bör inte hantera kollision med ett föremål som lagts på marken av en död fiende som
ett hinder och bör inte plocka upp föremålet.
- C7 - När spelaren går på ett föremål som lagts på marken av en död fiende, ska föremålet plockas
upp och den relevanta händelsen för det föremålet hända.
- F5 - Det bör finnas visuella specialeffekter som spelas på bestämda positioner på spelplanen när
specifika händelser sker.
-F6 - Inga rörliga föremål ska varken kunna röra sig eller existera utanför spelplanen. *



### Vecka 50
- Kodrapport
- Designspecifikation
- Dokumentering av kod
- Individuella portfolio-inlägget
- Reflektionsdokumentet
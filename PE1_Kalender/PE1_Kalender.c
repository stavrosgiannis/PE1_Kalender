#define _CRT_SECURE_NO_WARNINGS 1

#include <stdlib.h>
#include <stdio.h>

struct datum
{
	int dd;
	int mm;
	int yyyy;
};

#define TRUE    1
#define FALSE   0

int tage_im_monat[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

int julianische_wochentage[] = { 0/*Sonntag*/,1 /*Montag*/, 2/*Dienstag*/, 3/*Mittwoch*/, 4/*Donnerstag*/, 5/*Freitag*/, 6/*Samstag*/ };
int julianische_monate[] = { 1/*März*/, 2/*April*/, 3/*Mai*/, 4/*Juni*/, 5/*Juli*/, 6/*August*/, 7/*September*/, 8/*Oktober*/, 9/*November*/, 10/*Dezember*/, 11/*Januar*/, 12/*Februar*/ };

char* monate[] =
{
	" ",
	"\n\n\nJanuar",
	"\n\n\nFebruar",
	"\n\n\nMärz",
	"\n\n\nApril",
	"\n\n\nMai",
	"\n\n\nJuni",
	"\n\n\nJuli",
	"\n\n\nAugust",
	"\n\n\nSeptember",
	"\n\n\nOktober",
	"\n\n\nNovember",
	"\n\n\nDezember"
};

int check_schaltjahr(struct datum input_datum[1])
{
	if (input_datum[0].yyyy % 4 == FALSE && input_datum[0].yyyy % 100 != FALSE || input_datum[0].yyyy % 400 == FALSE)
	{
		tage_im_monat[2] = 29;
		return TRUE;
	}
	else
	{
		tage_im_monat[2] = 28;
		return FALSE;
	}
}

unsigned char response;

/* schaltjahr.c
	berechnet, ob ein Jahr nach den Gregorianischen Kalender ein Schaltjahr ist.
	Achtung: Vor 1582 war jedes Jahr mit durch 4 teilbarer Zahl ein Schaltjahr
	(Julianischer Kalender). */

int main() {
	do
	{
		struct datum input_datum[1];

		printf("Bitte geben Sie das Datum ein [dd.mm.yyyy]: ");
		scanf("%d.%d.%d", &input_datum[0].dd, &input_datum[0].mm, &input_datum[0].yyyy);

		//check_date(input_datum);

		//printf("%d DEBUG", tage_im_monat[input_datum[0].mm]);

		//Größe eines Arrays ermitteln
		size_t n = sizeof(tage_im_monat) / sizeof(tage_im_monat[0]);
		n = n - 1;

		if (input_datum[0].mm > 0 && input_datum[0].mm <= n) {
			printf("\nDer eingegebene Monat ist korrekt.\n");
		}
		else
		{
			printf("\nDer eingegebene Monat ist nicht korrekt.");
		}
		if (tage_im_monat[input_datum[0].mm] == input_datum[0].dd || (input_datum[0].dd > 0 && input_datum[0].dd <= tage_im_monat[input_datum[0].mm] + 1)) {
			printf("\nDer eingegebene Tag ist korrekt.\n");
		}
		else
		{
			printf("\nDer eingegebene Tag ist nicht korrekt!\n");
		}
		if (input_datum[0].yyyy > 0) {
			printf("\nDas eingegebene Jahr ist korrekt.\n");
		}
		else
		{
			printf("\nDas eingegebene Jahr ist nicht korrekt!\n");
		}

		printf("daycode: %d", kalender_wochentag_zähler(input_datum));

		if (check_schaltjahr(input_datum) == TRUE) {
			printf("\n%d ist ein Schaltjahr\n", input_datum[0].yyyy);
		}
		else {
			printf("\n%d ist kein Schaltjahr\n", input_datum[0].yyyy);
		}

		printf("\nTag im Jahr: %d", tag_im_jahr(input_datum));

		printf("\nDatum: %d.%d.%d", input_datum[0].dd, input_datum[0].mm, input_datum[0].yyyy);

		printf("\n\nerneute Berechnung? (j/n)\n");
		scanf("%c", &response);
	} while (getchar() == 'j' || getchar() == 'J');
}

int kalender_wochentag_zähler(struct datum input_datum[1])
{
	int tagcode;
	int d1, d2, d3;

	d1 = (input_datum[0].yyyy - 1.) / 4.0;
	d2 = (input_datum[0].yyyy - 1.) / 100.;
	d3 = (input_datum[0].yyyy - 1.) / 400.;
	tagcode = (input_datum[0].yyyy + d1 - d2 + d3) % 7;
	return tagcode;
}

int tag_im_jahr(struct datum input_datum[1])
{
	int tag_im_jahr = 0;

	for (int i = 1; i < input_datum[0].mm; i++) {
		tag_im_jahr = tag_im_jahr + tage_im_monat[i];
		if (i == input_datum[0].mm - 1) {
			tag_im_jahr = tag_im_jahr + input_datum[0].dd;
		}
	}
	return tag_im_jahr;
}

/*

In dieser Aufgabe soll ein C-Programm zur Erzeugung eines Kalenders erstellt werden. Ausgangspunkt ist ein vom Benutzer eingegebenes Datum, für das die Kalenderinformationen angezeigt werden sollen.

Die Funktionalität soll schrittweise realisiert werden. Achten Sie darauf, dass Sie für jeden Schritt jeweils zuerst ein Konzept haben, bevor Sie es anschließend umsetzen. Für die Aufgabe in dieser Woche existiert keine Vorlage. Sie können jedoch Teile der Programme aus den vergangenen Wochen nutzen, um beispielsweise die Benutzereingabe zu realisieren.

	1.	Berechnen Sie, ob das Jahr des vom Benutzer eingegebenen Datums ein Schaltjahr ist. FERTIG
	2.	Prüfen Sie, ob ein korrektes Datum eingegeben wurde. (Beachten Sie dabei auch die im ersten Teil ermittelte Information.) FERTIG
	3.	Geben Sie für den gegebenen Tag aus, der wievielte Tag des Jahres er ist.	FERTIG
	4.	Berechnen Sie den Wochentag des 1. Januars des gegebenen Jahres. (Zur Vereinfachung beschränken Sie ihr Programm auf
		Jahre des 20. oder 21. Jahrhunderts, also zwischen 1901 und 2100.)
	5.	Ermitteln Sie den Wochentag des gegebenen Tags.
	6.	Zusatzaufgabe: Berechnen Sie, in welcher Kalenderwoche der gegebene Tag ist (nach ISO 8601).

*/
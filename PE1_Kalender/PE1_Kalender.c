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

char wochentage[7][32] = { "Sonntag", "Montag","Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag" };
int monate[] = { 1/*März*/, 2/*April*/, 3/*Mai*/, 4/*Juni*/, 5/*Juli*/, 6/*August*/, 7/*September*/, 8/*Oktober*/, 9/*November*/, 10/*Dezember*/, 11/*Januar*/, 12/*Februar*/ };

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
			printf("\nDer eingegebene Monat ist korrekt.");
		}
		else
		{
			printf("\nDer eingegebene Monat ist nicht korrekt.");
		}
		if (tage_im_monat[input_datum[0].mm] == input_datum[0].dd || (input_datum[0].dd > 0 && input_datum[0].dd <= tage_im_monat[input_datum[0].mm] + 1)) {
			printf("\nDer eingegebene Tag ist korrekt.");
		}
		else
		{
			printf("\nDer eingegebene Tag ist nicht korrekt!");
		}
		if (input_datum[0].yyyy > 0) {
			printf("\nDas eingegebene Jahr ist korrekt.\n");
		}
		else
		{
			printf("\nDas eingegebene Jahr ist nicht korrekt!\n");
		}

		if (check_schaltjahr(input_datum) == TRUE) {
			printf("\n%d ist ein Schaltjahr", input_datum[0].yyyy);
		}
		else {
			printf("\n%d ist kein Schaltjahr", input_datum[0].yyyy);
		}

		printf("\nTag im Jahr: %d", tag_im_jahr(input_datum));

		printf("\nDatum: %d.%d.%d, ", input_datum[0].dd, input_datum[0].mm, input_datum[0].yyyy);
		getWochentag(input_datum);

		printf("\n%d. Woche im Jahr", aufgabe6(input_datum));

		printf("\n01.01.%d, ", input_datum[0].yyyy);
		/*printf("%d", dayofweek(input_datum[0].dd, input_datum[0].mm, input_datum[0].yyyy));*/
		aufgabe4(input_datum);
		//aufgabe5(input_datum);

		printf("\n\nerneute Berechnung? (j/n)\n");
		scanf("%c", &response);
	} while (getchar() == 'j' || getchar() == 'J');
}

int aufgabe5(struct datum input_datum[1]) {
	int num = input_datum[0].yyyy;
	int letzen_zwei_stellen_vorjahr[] = { 0,0 };
	int ersten_zwei_stellen_vorjahr[] = { 0,0 };

	for (int i = 0; i < 4; i++)
	{
		int mod = num % 10;  //split last digit from number
		printf("%d\n", mod); //print the digit.
		if (i == 0) {
			letzen_zwei_stellen_vorjahr[1] = mod;
		}
		else if (i == 1) {
			letzen_zwei_stellen_vorjahr[0] = mod;
		}
		else if (i == 3) {
			ersten_zwei_stellen_vorjahr[0] = mod;
		}
		else if (i == 4) {
			ersten_zwei_stellen_vorjahr[1] = mod;
		}

		num = num / 10;    //divide num by 10. num /= 10 also a valid one
	}
	/*printf("\n%d%d letzten stellen\n", letzen_zwei_stellen_vorjahr[0], letzen_zwei_stellen_vorjahr[1]);
	printf("\n%d%d ersten stellen\n", ersten_zwei_stellen_vorjahr[0], ersten_zwei_stellen_vorjahr[1]);*/
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

int dayofweek(int d, int m, int y)
{
	int s = 0, k, l, o, t, z1, z2, z3, z4, z5, z6;
	double p, z;
	z = (0.6 + (1.0 / m));
	k = (int)z;
	l = y - k;
	o = m + 12 * k;
	p = l / 100.0;
	z = p / 4.0;
	z1 = (int)z;
	z2 = (int)p;
	z = (5.0 * l) / 4.0;
	z3 = (int)z;
	z = (13.0 * (o + 1) / 5.0);
	z4 = (int)z;
	z5 = z4 + z3 - z2 + z1 + d - 1;
	z = z5 / 7.0;
	z6 = (int)z;
	t = z5 - (7 * z6) + 1;
	return(t - 1);
}

int getWochentag(struct datum input_datum[1]) {
	printf("%s", wochentage[dayofweek(input_datum[0].dd, input_datum[0].mm, input_datum[0].yyyy)]);
	/*return wochentage[dayofweek(input_datum[0].dd - 1, input_datum[0].mm, input_datum[0].yyyy)];*/
}

int aufgabe4(struct datum input_datum[1]) {
	input_datum[0].dd = 01;
	input_datum[0].mm = 01;
	getWochentag(input_datum);
	return 0;
}

int aufgabe6(struct datum input_datum[1]) {
	int woche_im_jahr = tag_im_jahr(input_datum) / 7;
	return woche_im_jahr + 1;
}

/*

In dieser Aufgabe soll ein C-Programm zur Erzeugung eines Kalenders erstellt werden. Ausgangspunkt ist ein vom Benutzer eingegebenes Datum, für das die Kalenderinformationen angezeigt werden sollen.

Die Funktionalität soll schrittweise realisiert werden. Achten Sie darauf, dass Sie für jeden Schritt jeweils zuerst ein Konzept haben, bevor Sie es anschließend umsetzen. Für die Aufgabe in dieser Woche existiert keine Vorlage. Sie können jedoch Teile der Programme aus den vergangenen Wochen nutzen, um beispielsweise die Benutzereingabe zu realisieren.

	1.	Berechnen Sie, ob das Jahr des vom Benutzer eingegebenen Datums ein Schaltjahr ist. FERTIG
	2.	Prüfen Sie, ob ein korrektes Datum eingegeben wurde. (Beachten Sie dabei auch die im ersten Teil ermittelte Information.) FERTIG
	3.	Geben Sie für den gegebenen Tag aus, der wievielte Tag des Jahres er ist.	FERTIG
	4.	Berechnen Sie den Wochentag des 1. Januars des gegebenen Jahres. (Zur Vereinfachung beschränken Sie ihr Programm auf
		Jahre des 20. oder 21. Jahrhunderts, also zwischen 1901 und 2100.) FERTIG
	5.	Ermitteln Sie den Wochentag des gegebenen Tags. FERTIG
	6.	Zusatzaufgabe: Berechnen Sie, in welcher Kalenderwoche der gegebene Tag ist (nach ISO 8601).

*/
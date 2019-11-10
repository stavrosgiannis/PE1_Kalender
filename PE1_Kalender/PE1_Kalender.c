#define _CRT_SECURE_NO_WARNINGS 1

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Deklarationen
unsigned char response;

struct datum
{
	unsigned int dd;
	unsigned int mm;
	unsigned int yyyy;
};

int days_of_month[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

const unsigned char julianische_wochentage[7][32] = { "Sonntag", "Montag","Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag" };
const unsigned int julianische_monate[] = { 1/*März*/, 2/*April*/, 3/*Mai*/, 4/*Juni*/, 5/*Juli*/, 6/*August*/, 7/*September*/, 8/*Oktober*/, 9/*November*/, 10/*Dezember*/, 11/*Januar*/, 12/*Februar*/ };

int getLeapYear(struct datum input_datum[1])
{
	if (input_datum[0].yyyy % 4 == 0 && input_datum[0].yyyy % 100 != 0 || input_datum[0].yyyy % 400 == 0)
	{
		days_of_month[2] = 29;
		return 1;
	}
	else
	{
		days_of_month[2] = 28;
		return 0;
	}
}

void SHOW_ASCII() {
	printf("______ _____ __    _   __      _                _\n"
		"| ___ |  ___/  |  | | / /     | |               | |          \n"
		"| |_/ / |__ `| |  | |/ /  __ _| | ___ _  __   __| | ___ _ __ \n"
		"|  __/|  __| | |  |    | / _` | |/ _ | '_  | / _` |/ _ \ __|\n"
		"| |   | |____| |_ | ||  | (_| | | __/| | | |(_| | || __/ |   \n"
		"|_|   |____/|___/ |_| |_/|__,_|_||___|_| |_| |__,_||___|_|  \n"
		"By Stavros Giannis\n"
		"______________________________________________________________________________\n");
}

int validateDate(struct datum input_datum[1]) {
	if (days_of_month[input_datum[0].mm] == input_datum[0].dd || (input_datum[0].dd > 0 && input_datum[0].dd <= days_of_month[input_datum[0].mm])) {
		//printf("\nDer eingegebene Tag ist korrekt.");
		if (input_datum[0].mm > 0 && input_datum[0].mm <= 12) {
			//printf("\nDer eingegebene Monat ist korrekt.");
			if (input_datum[0].yyyy > 0) {
				//printf("\nDas eingegebene Jahr ist korrekt.\n");
				return 1;
			}
		}
	}
	else
	{
		return 0;
	}
}

int main() {
	SHOW_ASCII();
	do
	{
		struct datum input_datum[1];

		printf("Bitte geben Sie das Datum ein [dd.mm.yyyy]: ");
		scanf("%d.%d.%d", &input_datum[0].dd, &input_datum[0].mm, &input_datum[0].yyyy);

		//Schaltjahr abfrage
		getLeapYear(input_datum);

		if (validateDate(input_datum) == 0) {
			printf("\n[Fehler] Das angegebene Datum ist nicht korrekt!");
		}

		if (getLeapYear(input_datum) == 1) {
			printf("\n%d ist ein Schaltjahr", input_datum[0].yyyy);
		}
		else {
			printf("\n%d ist kein Schaltjahr", input_datum[0].yyyy);
		}

		printf("\nTag im Jahr: %d", getDayOfYear(input_datum));

		printf("\nDatum: %d.%d.%d, ", input_datum[0].dd, input_datum[0].mm, input_datum[0].yyyy);
		getWeekday(input_datum);

		printf("\n%d. Woche im Jahr", getWeekInYear(input_datum));

		if (ISO8601(input_datum) != 1) {
			printf("\n[Fehler] Es gibt ein Problem beim ausführen der Funktion 'ISO8601'.");
		}

		if (static_date(input_datum) != 1) {
			printf("\n[Fehler] Es gibt ein Problem beim ausführen der Funktion 'static_date'.");
		}

		printf("\n\nerneute Berechnung? (j/n)\n");
		scanf("%c", &response);
	} while (getchar() == 'j' || getchar() == 'J');
}

int getDayOfYear(struct datum input_datum[1])
{
	int tag_im_jahr = 0;

	for (int i = 1; i < input_datum[0].mm; i++) {
		tag_im_jahr = tag_im_jahr + days_of_month[i];
		if (i == input_datum[0].mm - 1) {
			tag_im_jahr = tag_im_jahr + input_datum[0].dd;
		}
	}
	return tag_im_jahr;
}

int getDayOfWeek(int d, int m, int y)
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

int getWeekday(struct datum input_datum[1]) {
	printf(julianische_wochentage[getDayOfWeek(input_datum[0].dd, input_datum[0].mm, input_datum[0].yyyy)]);
}

int static_date(struct datum input_datum[1]) {
	input_datum[0].dd = 01;
	input_datum[0].mm = 01;
	printf("\n01.01.%d, ", input_datum[0].yyyy);
	getWeekday(input_datum);
	return 1;
}

int getWeekInYear(struct datum input_datum[1]) {
	int woche_im_jahr = getDayOfYear(input_datum) / 7;
	return woche_im_jahr + 1;
}

int ISO8601(struct datum input_datum[1]) {
	// YYYY-Www-D
	if (input_datum[0].dd < 10 && getWeekInYear(input_datum) < 10) {
		printf("\nISO8601: %d-W0%d-0%d", input_datum[0].yyyy, getWeekInYear(input_datum), input_datum[0].dd);
		return 1;
	}
	else if (input_datum[0].dd < 10 && getWeekInYear(input_datum) < 10) {
		printf("\nISO8601: %d-W%d-0%d", input_datum[0].yyyy, getWeekInYear(input_datum), input_datum[0].dd);
		return 1;
	}
	else if (input_datum[0].dd > 10 && getWeekInYear(input_datum) < 10) {
		printf("\nISO8601: %d-W0%d-%d", input_datum[0].yyyy, getWeekInYear(input_datum), input_datum[0].dd);
		return 1;
	}
	else {
		printf("\nISO8601: %d-W%d-%d", input_datum[0].yyyy, getWeekInYear(input_datum), input_datum[0].dd);
		return 1;
	}

	return 0;
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
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdlib.h>
#include <stdio.h>

struct datum
{
	int dd;
	int mm;
	int yyyy;
};

unsigned char response;

/* schaltjahr.c
	berechnet, ob ein Jahr nach den Gregorianischen Kalender ein Schaltjahr ist.
	Achtung: Vor 1582 war jedes Jahr mit durch 4 teilbarer Zahl ein Schaltjahr
	(Julianischer Kalender). */

int schalt(int j) {
	if (j % 4 == 0 && j % 100 != 0 || j % 400 == 0)
		return 1;
	else
		return 0;
}

int main() {
	do
	{
		struct datum input_date[1];

		printf("Gib den Tag deines Datums ein [dd].mm.yyyy ein: ");
		scanf("%d", &input_date[0].dd);
		while (getchar() != '\n');
		printf("Gib den Monat deines Datums ein dd.[mm].yyyy ein: ");
		scanf("%d", &input_date[0].mm);
		while (getchar() != '\n');
		printf("Gib das Jahr deines Datums ein dd.mm.[yyyy] ein: ");
		scanf("%d", &input_date[0].yyyy);

		if (schalt(input_date[0].yyyy))
			printf("%d ist ein Schaltjahr\n", input_date[0].yyyy);
		else
			printf("%d ist kein Schaltjahr\n", input_date[0].yyyy);

		printf("Datum: %d.%d.%d", input_date[0].dd, input_date[0].mm, input_date[0].yyyy);

		printf("\n\nerneute Berechnung? (j/n)\n");
		scanf("%c", &response);
	} while (getchar() == 'j' || getchar() == 'J');
}

/*

In dieser Aufgabe soll ein C-Programm zur Erzeugung eines Kalenders erstellt werden. Ausgangspunkt ist ein vom Benutzer eingegebenes Datum, für das die Kalenderinformationen angezeigt werden sollen.

Die Funktionalität soll schrittweise realisiert werden. Achten Sie darauf, dass Sie für jeden Schritt jeweils zuerst ein Konzept haben, bevor Sie es anschließend umsetzen. Für die Aufgabe in dieser Woche existiert keine Vorlage. Sie können jedoch Teile der Programme aus den vergangenen Wochen nutzen, um beispielsweise die Benutzereingabe zu realisieren.

	1.	Berechnen Sie, ob das Jahr des vom Benutzer eingegebenen Datums ein Schaltjahr ist. FERTIG
	2.	Prüfen Sie, ob ein korrektes Datum eingegeben wurde. (Beachten Sie dabei auch die im ersten Teil ermittelte Information.)
	3.	Geben Sie für den gegebenen Tag aus, der wievielte Tag des Jahres er ist.
	4.	Berechnen Sie den Wochentag des 1. Januars des gegebenen Jahres. (Zur Vereinfachung beschränken Sie ihr Programm auf
		Jahre des 20. oder 21. Jahrhunderts, also zwischen 1901 und 2100.)
	5.	Ermitteln Sie den Wochentag des gegebenen Tags.
	6.	Zusatzaufgabe: Berechnen Sie, in welcher Kalenderwoche der gegebene Tag ist (nach ISO 8601).

*/
#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_paf_bucket : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_paf_bucket() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_paf_bucket() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_PAF_BUCKET")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Purchase Accumulation File (PAF) bucket.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Purchase Accumulation File (PAF) bucket.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Purchase Accumulation File (PAF)-Speicherbereich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sector de almacenamiento de archivo de acumulación de compras (PAF) no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Catégorie de fichier d'accumulation d'achat invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige PAF bucket (Purchase Accumulation File)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Eintrag. Wenn der Eintrag richtig ist, wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie. Si elle est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de invoer. Als de invoer juist is, neemt u contact op met een medewerker van de klantendienst en meldt u dit bericht")); }
	};
}




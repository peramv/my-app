#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_ad_shareholder_does_not_exist : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_ad_shareholder_does_not_exist() { }
		~CIFast_Infrastructure_ifastdbrkr_err_ad_shareholder_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_SHAREHOLDER_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Management Company not found on the Fund Literals File (A52).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Management Company not found on the Fund Literals File (A52).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Management-Unternehmen nicht in den Fund-Literals-Dateien (A52) gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la compañía administradora en el archivo Fund Literals (A52).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Entreprise de gestion introuvable dans le fichier textuel de fonds (A52)")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Beheerbedrijf niet gevonden in Fund Literals File (A52)")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify management company. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify management company. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Management-Unternehmen. Wenn der Eintrag richtig ist, wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify management company. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'entreprise de gestion. Si la saisie est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het beheerbedrijf. Als de invoer juist is, neemt u contact op met een medewerker van de klantendienst en meldt u dit bericht")); }
	};
}




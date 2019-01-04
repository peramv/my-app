#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfdata_cnd_invalidcharacterexception : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfdata_cnd_invalidcharacterexception() { }
		~CBase_Infrastructure_bfdata_cnd_invalidcharacterexception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("CND_InvalidCharacterException")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfdata")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Financial institution information not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Financial institution information not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Finanzinstitut-Information nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró información sobre la institución financiera.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information sur l'institution financière introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens financiële instelling zijn niet gevonden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify financial institution information. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify financial institution information. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Finanzinstitut-Informationen. Wenn der Eintrag richtig ist, wenden Sie sich an einen Kundendienstmitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique los datos de la institución financiera. Si los datos son correctos, notifique de este mensaje a un representante de servicio al cliente.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'information sur l'institution financière. Si la saisie est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de gegevens van de financiële instelling. Als de invoer juist is, neemt u contact op met een medewerker van de klantendienst en meldt u dit bericht")); }
	};
}




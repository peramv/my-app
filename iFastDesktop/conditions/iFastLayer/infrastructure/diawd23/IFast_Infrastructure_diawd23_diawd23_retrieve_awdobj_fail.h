#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_diawd23_diawd23_retrieve_awdobj_fail : public CConditionObject
	{
	public:
		CIFast_Infrastructure_diawd23_diawd23_retrieve_awdobj_fail() { }
		~CIFast_Infrastructure_diawd23_diawd23_retrieve_awdobj_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_RETRIEVE_AWDOBJ_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD information could not be retrieved.\n\nSystem could not get AWD object from server database. Return Code = %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD information could not be retrieved.\n\nSystem could not get AWD object from server database. Return Code = %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Information konnte nicht ausgelesen werden.\n\nSystem konnte AWD-Objekt nicht aus der Serverdatenbank abrufen. Return Code = %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puedo recuperar información de AWD.\n\nEl sistema no puedo recibir el objeto AWD de la base de datos del servidor. Código de retorno = %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information AWD n'a pu être récupérée. \n\n Le système n'a pas pu obtenir l'objet AWD de la base de données du serveur. Code de renvoi : %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-gegevens konden niet worden opgehaald.\nSysteem kon AWD-object niet ophalen van de serverdatabase. Retourcode = %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}




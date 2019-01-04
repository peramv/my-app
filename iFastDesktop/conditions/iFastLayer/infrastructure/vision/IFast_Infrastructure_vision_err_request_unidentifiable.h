#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_vision_err_request_unidentifiable : public CConditionObject
	{
	public:
		CIFast_Infrastructure_vision_err_request_unidentifiable() { }
		~CIFast_Infrastructure_vision_err_request_unidentifiable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REQUEST_UNIDENTIFIABLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal connection problem. A connection to the AWD32 OLE interface could not be made.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal connection problem. A connection to the AWD32 OLE interface could not be made.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Verbindungs-Problem. Eine Verbindung mit dem AWD32 OLE-Interface konnte nicht hergestellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema de conexión interno. No se pudo realizar una conexión con la interfaz AWD32 OLE.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème de connexion interne. Une connexion à l'interface AWD32 n'a pu être établie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern verbindingsprobleem. Een verbinding met de AWD32 OLE-interface kon niet worden gemaakt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}




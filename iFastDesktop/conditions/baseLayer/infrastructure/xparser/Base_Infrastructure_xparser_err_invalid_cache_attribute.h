#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_err_invalid_cache_attribute : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_err_invalid_cache_attribute() { }
		~CBase_Infrastructure_xparser_err_invalid_cache_attribute() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CACHE_ATTRIBUTE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Virtual method in base class not supported.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Virtual method in base class not supported.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Die virtuelle Methode wird in der Basisklasse nicht unterstützt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. El sistema no soporta el método virtual en la clase básica.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. La méthode virtuelle dans la classe de base n'est pas supportée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Virtuele methode in basiscategorie wordt niet ondersteund")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}




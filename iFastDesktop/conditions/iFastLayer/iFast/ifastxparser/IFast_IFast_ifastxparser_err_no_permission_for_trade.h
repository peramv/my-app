#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastxparser_err_no_permission_for_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastxparser_err_no_permission_for_trade() { }
		~CIFast_IFast_ifastxparser_err_no_permission_for_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_PERMISSION_FOR_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastxparser")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User is not permitted to trade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzer ist für den Handel nicht zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite al usuario realizar una operación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'est pas autorisé à effectuer des transactions.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruiker mag niet handelen")); }

        // Actions
	};
}




#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_wrong_last_banktype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_wrong_last_banktype() { }
		~CIFast_IFast_ifastdbrkr_err_wrong_last_banktype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WRONG_LAST_BANKTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Last Bank Type must either be EDE, PWE or PWI.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Letzte Bankart muss entweder EDE, PWE oder PWI sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El último tipo de banco debe ser EDE, PWE o PWI")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le dernier type de banque doit être EDE, PWE ou PWI.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Laatste banktype moet EDE, PWE of PWI zijn")); }

        // Actions
	};
}




#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_allocation_exists_for_fund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_allocation_exists_for_fund_class() { }
		~CIFast_IFast_ifastdbrkr_err_allocation_exists_for_fund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALLOCATION_EXISTS_FOR_FUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An allocation already exists for this Fund/Class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eine Zuweisung bereits für diesen Fonds/ diese Klasse vorhanden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ya existe una asignación para  este fondo/clase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une répartition existe déjà pour ce fonds/cette classe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaat al een allocatie voor dit fonds of deze categorie")); }

        // Actions
	};
}




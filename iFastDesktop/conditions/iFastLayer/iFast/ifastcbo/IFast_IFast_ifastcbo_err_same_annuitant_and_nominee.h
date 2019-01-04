#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_same_annuitant_and_nominee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_same_annuitant_and_nominee() { }
		~CIFast_IFast_ifastcbo_err_same_annuitant_and_nominee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SAME_ANNUITANT_AND_NOMINEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Annuitant and Accountholder must be the same person.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le crédirentier et le titulaire du compte doivent être la même personne.")); }

        // Actions
	};
}




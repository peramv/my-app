#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_waive_paper_cannot_be_yes : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_waive_paper_cannot_be_yes() { }
		~CIFast_IFast_ifastcbo_warn_waive_paper_cannot_be_yes() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_WAIVE_PAPER_CANNOT_BE_YES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Waive paper can not be set to yes when CD, FAX, EMAIL and EPOST are all set to no for document type:  %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Waive paper ne peut pas être « oui » si les champs CD, Télécopieur, Courriel et Postel sont tous « non » pour ce type de document : %DOCTYPE%.")); }

        // Actions
	};
}




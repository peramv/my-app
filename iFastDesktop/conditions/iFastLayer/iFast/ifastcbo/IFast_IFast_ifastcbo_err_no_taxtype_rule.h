#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_taxtype_rule : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_taxtype_rule() { }
		~CIFast_IFast_ifastcbo_err_no_taxtype_rule() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_TAXTYPE_RULE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Tax Type Rules are setup for the combination of account Tax Type and Pension Jurisdiction, cannot process Cash Redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No Tax Type Rules are setup for the combination of account Tax Type and Pension Jurisdiction, cannot process Cash Redemption.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No Tax Type Rules are setup for the combination of account Tax Type and Pension Jurisdiction, cannot process Cash Redemption.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune règle de type d'imposition n'est réglée pour la combinaison de type d'imposition et de juridiction de retraite du compte, impossible de procéder au rachat au comptant.")); }

        // Actions
	};
}




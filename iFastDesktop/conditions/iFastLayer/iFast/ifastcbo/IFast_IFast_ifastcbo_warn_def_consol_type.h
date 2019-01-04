#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_def_consol_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_def_consol_type() { }
		~CIFast_IFast_ifastcbo_warn_def_consol_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DEF_CONSOL_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is a mismatch between Consolidation Type value in the generic control and this record.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a une discordance entre la valeur du type de consolidation dans le contrôle générique et cet enregistrement.")); }

        // Actions
	};
}




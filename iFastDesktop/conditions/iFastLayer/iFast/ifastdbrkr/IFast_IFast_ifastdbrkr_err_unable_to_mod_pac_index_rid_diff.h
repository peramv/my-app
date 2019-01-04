#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_to_mod_pac_index_rid_diff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_to_mod_pac_index_rid_diff() { }
		~CIFast_IFast_ifastdbrkr_err_unable_to_mod_pac_index_rid_diff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_MOD_PAC_INDEX_RID_DIFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify PAC-Index record, version numbers are different.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("PAC-Indexeintrag konnte nicht geändert werden, die Versionsnummern sind verschieden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible modificar el registro de índice PAC, los números de versión son diferentes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier l'enregistrement d'indexation PAC, les numéros de versions sont différents.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record VGC-Index kon niet worden gewijzigd, de versienummers zijn verschillend")); }

        // Actions
	};
}




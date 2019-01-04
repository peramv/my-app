#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_batch_name_has_been_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_batch_name_has_been_changed() { }
		~CIFast_IFast_ifastcbo_warn_batch_name_has_been_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BATCH_NAME_HAS_BEEN_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The active Batch Name has been changed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der aktive Batch-Name wurde geändert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se ha modificado el nombre del lote activo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nom du lot actif a été changé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De actieve batchnaam is gewijzigd")); }

        // Actions
	};
}




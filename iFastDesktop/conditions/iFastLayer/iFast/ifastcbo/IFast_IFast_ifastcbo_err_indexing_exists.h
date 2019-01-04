#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_indexing_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_indexing_exists() { }
		~CIFast_IFast_ifastcbo_err_indexing_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INDEXING_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Indexing exists. Indexing must be deleted before frequency can be modified.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Indexierung existiert. Indexierung muss gelöscht werden, bevor die Häufigkeit geändert werden kann.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El índice existe. Debe eliminarse el índice antes de poder modificar la frecuencia.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Indexation existante. L'indexation doit être supprimée avant que la fréquence ne puisse être modifiée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Indexering bestaat. Indexering moet worden gewist voordat de frequentie kan worden gewijzigd")); }

        // Actions
	};
}




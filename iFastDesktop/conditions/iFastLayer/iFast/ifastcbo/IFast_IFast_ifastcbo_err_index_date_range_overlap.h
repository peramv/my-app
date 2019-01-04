#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_index_date_range_overlap : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_index_date_range_overlap() { }
		~CIFast_IFast_ifastcbo_err_index_date_range_overlap() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INDEX_DATE_RANGE_OVERLAP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The date range in this index overlaps an existing index.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieser Datumsbereich in diesem Index überschneidet sich mit einem existierenden Index.  Bitte ändern Sie den Datumsbereich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El rango de fechas de este índice se superpone con un índice existente.  Por favor cambie el rango de fechas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La plage de dates d'indexation chevauche l'indexation existante.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit datumbereik in deze index overlapt een bestaande index.  Wijzig het datumbereik")); }

        // Actions
	};
}




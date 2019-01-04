#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_index_date_later_than_end_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_index_date_later_than_end_date() { }
		~CIFast_IFast_ifastcbo_err_index_date_later_than_end_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INDEX_DATE_LATER_THAN_END_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Next Index Date cannot be after the End Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nächstes Indexdatum darf nicht größer als das Enddatum sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de índice siguiente no puede ser posterior a la fecha de terminación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La prochaine date d'indexation ne peut être postérieure à la date de fin.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volgende indexdatum mag niet later zijn dan de einddatum")); }

        // Actions
	};
}




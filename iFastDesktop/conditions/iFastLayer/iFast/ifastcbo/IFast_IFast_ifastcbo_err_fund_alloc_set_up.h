#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_alloc_set_up : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_alloc_set_up() { }
		~CIFast_IFast_ifastcbo_err_fund_alloc_set_up() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_ALLOC_SET_UP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Allocation exists when Global Level Asset Mix indicates not applicable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("FundAlloc darf nicht auf Nein gestellt werden, bevor die Zuweisungsliste gelöscht ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede configurar FundAlloc en No antes de eliminar la lista de asignaciones.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La répartition de fonds existe lorsque la composition d'actif de niveau global indique Sans objet.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fondsallocatie kan niet worden ingesteld op nee voordat allocatielijst is gewist")); }

        // Actions
	};
}




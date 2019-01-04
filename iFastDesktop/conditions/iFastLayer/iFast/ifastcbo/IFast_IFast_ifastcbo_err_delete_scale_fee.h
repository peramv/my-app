#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_delete_scale_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_delete_scale_fee() { }
		~CIFast_IFast_ifastcbo_err_delete_scale_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DELETE_SCALE_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Scale Fee can not be deleted because process date is different from current business date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Gebühr kann nicht gelöscht werden, weil sich das Verarbeitungsdatum vom aktuellen Geschäftsdatum unterscheidet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede eliminar la comisión de escala ya que la fecha de proceso es diferente de la fecha de negocios actual.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les frais de l'échelle ne peuvent être supprimés car la date de traitement est différente de la date opérationnelle actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Schalingskosten kunnen niet worden gewist omdat de verwerkingsdatum verschilt van de huidige werkdag")); }

        // Actions
	};
}




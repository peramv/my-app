#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_delivery_method_exists_for_doc_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_delivery_method_exists_for_doc_type() { }
		~CIFast_IFast_ifastdbrkr_err_delivery_method_exists_for_doc_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DELIVERY_METHOD_EXISTS_FOR_DOC_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Delivery Method already exists for document type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Liefermethode für diesen Dokumenttyp existiert bereits.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ya existe un método de entrega para este tipo de documento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La méthode de livraison existe déjà pour le type de document.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Leveringsmethode bestaat al voor documenttype")); }

        // Actions
	};
}




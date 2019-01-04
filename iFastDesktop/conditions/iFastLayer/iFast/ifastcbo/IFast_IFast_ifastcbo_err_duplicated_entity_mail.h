#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicated_entity_mail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicated_entity_mail() { }
		~CIFast_IFast_ifastcbo_err_duplicated_entity_mail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATED_ENTITY_MAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicated mailing for document type %DOCTYPE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Doppeltes Mailing für Dokumentart %DOCTYPE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Envío de correspondencia repetido para el tipo de documento %DOCTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie postale pour le type de document %DOCTYPE%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dubbele mailing voor documenttype %DOCTYPE%")); }

        // Actions
	};
}




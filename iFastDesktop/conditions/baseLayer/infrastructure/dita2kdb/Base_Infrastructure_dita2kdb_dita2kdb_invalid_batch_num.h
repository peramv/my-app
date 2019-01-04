#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_invalid_batch_num : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_invalid_batch_num() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_invalid_batch_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_BATCH_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this batch number. Verify batch number and re-enter.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this batch number. Verify batch number and re-enter.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Batch-Nummer nicht. Bestätigen Sie die Batch-Nummer und geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este número de lote. Verifique el número de lote y vuelva a introducirlo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce numéro de lot. Vérifiez le numéro de lot et réessayez.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit batchnummer niet. Controleer het batchnummer en voer het opnieuw in")); }

        // Actions
	};
}




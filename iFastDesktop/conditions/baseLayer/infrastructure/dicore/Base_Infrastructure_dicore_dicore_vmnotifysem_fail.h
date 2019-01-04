#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dicore_vmnotifysem_fail : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dicore_vmnotifysem_fail() { }
		~CBase_Infrastructure_dicore_dicore_vmnotifysem_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_VMNOTIFYSEM_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VmNotifySem error.  Semaphore Name: %SEM%  Return Code: %RC%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("VmNotifySem error.  Semaphore Name: %SEM%  Return Code: %RC%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("VmNotifySem-Fehler.  Semaphorname: %SEM% Rückgabecode: %RC%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de VmNotifySem.  Nombre del semáforo: %SEM%  Código de retorno: %RC%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de sémaphore de notification du gestionnaire de l'affichage. Nom du sémaphore : %SEM%. Code de renvoi : %RC%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("VmNotifySem-fout.  Naam semafoor: %SEM%  Retourcode: %RC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}




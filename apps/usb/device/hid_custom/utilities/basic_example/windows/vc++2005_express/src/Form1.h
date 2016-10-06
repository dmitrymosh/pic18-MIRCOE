#pragma once
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------BEGIN CUT AND PASTE BLOCK-----------------------------------------------------------------------------------
/********************************************************************
 FileName:		Form1.h
 Dependencies:	Platform SDK during development.  When compiled, needs
				.NET framework 2.0 redistributable to run
 Processor:		x86 
 Hardware:		Need a free USB port to connect USB peripheral device
 Compiler:  	Microsoft Visual C++ 2005 Express Edition (or better)
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively with Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   04/08/2008   Initial release
  2.3	08/11/2008	 Slight update for improved robustness
  2.7a	08/29/2010	 Adding explicit calling conventions to the DllImports.
					 This is needed for Visual Studio 2010 compatibility.
					 No functional changes to the code.  Backwards compatibility
					 should be retained.
********************************************************************
NOTE:	All user made code contained in this project is in the Form1.h file.
		All other code and files were generated automatically by either the
		new project wizard, or by the development environment (ex: code is
		automatically generated if you create a new button on the form, and
		then double click on it, which creates a click event handler
		function).  All user made code is contained in clearly marked cut and
		paste blocks.
********************************************************************/

//Includes
#include <Windows.h>	//Definitions for various common and not so common types like DWORD, PCHAR, HANDLE, etc.
#include <setupapi.h>	//From Platform SDK. Definitions needed for the SetupDixxx() functions, which we use to
						//find our plug and play device.

//Modify this value to match the VID and PID in your USB device descriptor.
//Use the formatting: "Vid_xxxx&Pid_xxxx" where xxxx is a 16-bit hexadecimal number.
#define MY_DEVICE_ID  "Vid_04d8&Pid_003F"	
//-------------------------------------------------------END CUT AND PASTE BLOCK-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


namespace GenericHIDSimpleDemo {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------BEGIN CUT AND PASTE BLOCK-----------------------------------------------------------------------------------
	using namespace System::Runtime::InteropServices;  //Need this to support "unmanaged" code.

	/*
	In order to use these unmanaged functions from within the managed .NET environment, we need
	to explicitly import the functions which we will be using from other .DLL file(s).  Simply
	including the appropriate header files is not enough. 

	Note: In order to avoid potential name conflicts in the header files (which we still use),
	I have renamed the functions by adding "UM" (unmanaged) onto the end of them.  To find 
	documentation for the functions in MSDN, search for the function name without the extra 
	"UM" attached.
	Note2: In the header files (such as setupapi.h), normally the function names are 
	remapped, depending upon if UNICODE is defined or not.  For example, two versions of the
	function SetupDiGetDeviceInterfaceDetail() exist.  One for UNICODE, and one for ANSI.  
	If the wrong version of the function is called, things won't work correctly.  Therefore,
	in order to make sure the correct one gets called (based on your compiler settings, which
	may or may not define "UNICODE"), it is useful to explicity specify the CharSet when doing
	the DLL import.
	*/

	#ifdef UNICODE
	#define	Seeifdef	Unicode
	#else
	#define Seeifdef	Ansi
	#endif

	//Returns a HDEVINFO type for a device information set (USB HID devices in
	//our case).  We will need the HDEVINFO as in input parameter for calling many of
	//the other SetupDixxx() functions.
	[DllImport("setupapi.dll" , CharSet = CharSet::Seeifdef, EntryPoint="SetupDiGetClassDevs", CallingConvention=CallingConvention::Winapi)]		
	extern "C" HDEVINFO  SetupDiGetClassDevsUM(
		LPGUID  ClassGuid,					//Input: Supply the class GUID here. 
		PCTSTR  Enumerator,					//Input: Use NULL here, not important for our purposes
		HWND  hwndParent,					//Input: Use NULL here, not important for our purposes
		DWORD  Flags);						//Input: Flags describing what kind of filtering to use.

	//Gives us "PSP_DEVICE_INTERFACE_DATA" which contains the Interface specific GUID (different
	//from class GUID).  We need the interface GUID to get the device path.
	[DllImport("setupapi.dll" , CharSet = CharSet::Seeifdef, EntryPoint="SetupDiEnumDeviceInterfaces", CallingConvention=CallingConvention::Winapi)]				
	extern "C" WINSETUPAPI BOOL WINAPI  SetupDiEnumDeviceInterfacesUM(
		HDEVINFO  DeviceInfoSet,			//Input: Give it the HDEVINFO we got from SetupDiGetClassDevs()
		PSP_DEVINFO_DATA  DeviceInfoData,	//Input (optional)
		LPGUID  InterfaceClassGuid,			//Input 
		DWORD  MemberIndex,					//Input: "Index" of the device you are interested in getting the path for.
		PSP_DEVICE_INTERFACE_DATA  DeviceInterfaceData);//Output: This function fills in an "SP_DEVICE_INTERFACE_DATA" structure.

	//SetupDiDestroyDeviceInfoList() frees up memory by destroying a DeviceInfoList
	[DllImport("setupapi.dll" , CharSet = CharSet::Seeifdef, EntryPoint="SetupDiDestroyDeviceInfoList", CallingConvention=CallingConvention::Winapi)]
	extern "C" WINSETUPAPI BOOL WINAPI  SetupDiDestroyDeviceInfoListUM(			
		HDEVINFO  DeviceInfoSet);			//Input: Give it a handle to a device info list to deallocate from RAM.

	//SetupDiEnumDeviceInfo() fills in an "SP_DEVINFO_DATA" structure, which we need for SetupDiGetDeviceRegistryProperty()
	[DllImport("setupapi.dll" , CharSet = CharSet::Seeifdef, EntryPoint="SetupDiEnumDeviceInfo", CallingConvention=CallingConvention::Winapi)]
	extern "C" WINSETUPAPI BOOL WINAPI  SetupDiEnumDeviceInfoUM(
		HDEVINFO  DeviceInfoSet,
		DWORD  MemberIndex,
		PSP_DEVINFO_DATA  DeviceInfoData);

	//SetupDiGetDeviceRegistryProperty() gives us the hardware ID, which we use to check to see if it has matching VID/PID
	[DllImport("setupapi.dll" , CharSet = CharSet::Seeifdef, EntryPoint="SetupDiGetDeviceRegistryProperty", CallingConvention=CallingConvention::Winapi)]
	extern "C"	WINSETUPAPI BOOL WINAPI  SetupDiGetDeviceRegistryPropertyUM(
		HDEVINFO  DeviceInfoSet,
		PSP_DEVINFO_DATA  DeviceInfoData,
		DWORD  Property,
		PDWORD  PropertyRegDataType,
		PBYTE  PropertyBuffer,   
		DWORD  PropertyBufferSize,  
		PDWORD  RequiredSize);

	//SetupDiGetDeviceInterfaceDetail() gives us a device path, which is needed before CreateFile() can be used.
	[DllImport("setupapi.dll" , CharSet = CharSet::Seeifdef, EntryPoint="SetupDiGetDeviceInterfaceDetail", CallingConvention=CallingConvention::Winapi)]
	extern "C" BOOL SetupDiGetDeviceInterfaceDetailUM(
		HDEVINFO DeviceInfoSet,										//Input: Wants HDEVINFO which can be obtained from SetupDiGetClassDevs()
		PSP_DEVICE_INTERFACE_DATA DeviceInterfaceData,				//Input: Pointer to an structure which defines the device interface.  
		PSP_DEVICE_INTERFACE_DETAIL_DATA DeviceInterfaceDetailData,	//Output: Pointer to a strucutre, which will contain the device path.
		DWORD DeviceInterfaceDetailDataSize,						//Input: Number of bytes to retrieve.
		PDWORD RequiredSize,										//Output (optional): Te number of bytes needed to hold the entire struct 
		PSP_DEVINFO_DATA DeviceInfoData);							//Output


//  Variables that need to have wide scope.
	HANDLE WriteHandle = INVALID_HANDLE_VALUE;	//Need to get a write "handle" to our device before we can write to it.
	HANDLE ReadHandle = INVALID_HANDLE_VALUE;	//Need to get a read "handle" to our device before we can read from it.
	
	/** DEFINITIONS ****************************************************/
	typedef enum
	{
		COMMAND_GET_CONFIG = 0x80,
		COMMAND_SET_CONFIG = 0x81,
		COMMAND_LOAD_CONFIG = 0x82,
		COMMAND_SAVE_CONFIG = 0x83,
	} CUSTOM_HID_DEMO_COMMANDS;
	
	typedef WORD  uint16_t;
	typedef DWORD uint32_t;
	typedef INT16 int16_t;
	typedef INT32 int32_t;

	typedef struct 
	{
		uint16_t MainGearCogsCount;     
		uint16_t GearRatio;             
		uint16_t SM_StepCount;           
		uint16_t SM_uStepCount;               
		int16_t IntervalCorrection;         // step
		int32_t IntervalCorrection_1kk;     // step/1kk 
		uint16_t PulseWidth;                // in step    
		uint32_t TimerFrequency;            // in Hz
		uint16_t Interval;                  // step
		uint32_t Interval_1kk;              // step/1kk 
		uint32_t StarDayLength;
		uint32_t StarDayLength_1kk;
	} APP_CONFIG;

	bool NeedUpdate;
	
//-------------------------------------------------------END CUT AND PASTE BLOCK-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------


	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
		//void UpdateParams(APP_CONFIG * config);
	private: System::Windows::Forms::Button^  Connect_btn;
	private: System::Windows::Forms::Button^  SendConfigBtn;

	private: System::Windows::Forms::Button^  GetConfigBtn;
	protected: 


	private: System::Windows::Forms::Label^  StateLabel;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::NumericUpDown^  IntervalCorrection;


	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::NumericUpDown^  DriverPulseWigth;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::NumericUpDown^  DriverMicrostepCount;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::NumericUpDown^  MotorStepCount;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::NumericUpDown^  GearRatio;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::NumericUpDown^  MainGearCogsCount;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;


	private: System::Windows::Forms::GroupBox^  groupBox2;


	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  Interval;

	private: System::Windows::Forms::Label^  label14;

	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Button^  LoadConfigBtn;
	private: System::Windows::Forms::Button^  SaveConfigBtn;


	private: System::Windows::Forms::NumericUpDown^  StarDayLength;
	private: System::Windows::Forms::NumericUpDown^  TimerStepLength;



	private: System::Windows::Forms::NumericUpDown^  TimerFrequency;
	private: System::Windows::Forms::NumericUpDown^  IntervalSteps;

	private: System::Windows::Forms::NumericUpDown^  PulseWidthSteps;

	private: System::Windows::Forms::NumericUpDown^  IntervalMicroSec;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Connect_btn = (gcnew System::Windows::Forms::Button());
			this->SendConfigBtn = (gcnew System::Windows::Forms::Button());
			this->GetConfigBtn = (gcnew System::Windows::Forms::Button());
			this->StateLabel = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->TimerStepLength = (gcnew System::Windows::Forms::NumericUpDown());
			this->TimerFrequency = (gcnew System::Windows::Forms::NumericUpDown());
			this->StarDayLength = (gcnew System::Windows::Forms::NumericUpDown());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->IntervalCorrection = (gcnew System::Windows::Forms::NumericUpDown());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->DriverPulseWigth = (gcnew System::Windows::Forms::NumericUpDown());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->DriverMicrostepCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->MotorStepCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->GearRatio = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->MainGearCogsCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->IntervalSteps = (gcnew System::Windows::Forms::NumericUpDown());
			this->PulseWidthSteps = (gcnew System::Windows::Forms::NumericUpDown());
			this->IntervalMicroSec = (gcnew System::Windows::Forms::NumericUpDown());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->Interval = (gcnew System::Windows::Forms::Label());
			this->LoadConfigBtn = (gcnew System::Windows::Forms::Button());
			this->SaveConfigBtn = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TimerStepLength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TimerFrequency))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->StarDayLength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->IntervalCorrection))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DriverPulseWigth))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DriverMicrostepCount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MotorStepCount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->GearRatio))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MainGearCogsCount))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->IntervalSteps))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PulseWidthSteps))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->IntervalMicroSec))->BeginInit();
			this->SuspendLayout();
			// 
			// Connect_btn
			// 
			this->Connect_btn->Location = System::Drawing::Point(13, 13);
			this->Connect_btn->Name = L"Connect_btn";
			this->Connect_btn->Size = System::Drawing::Size(75, 23);
			this->Connect_btn->TabIndex = 0;
			this->Connect_btn->Text = L"Connect";
			this->Connect_btn->UseVisualStyleBackColor = true;
			this->Connect_btn->Click += gcnew System::EventHandler(this, &Form1::Connect_btn_Click);
			// 
			// SendConfigBtn
			// 
			this->SendConfigBtn->Enabled = false;
			this->SendConfigBtn->Location = System::Drawing::Point(177, 450);
			this->SendConfigBtn->Name = L"SendConfigBtn";
			this->SendConfigBtn->Size = System::Drawing::Size(125, 23);
			this->SendConfigBtn->TabIndex = 1;
			this->SendConfigBtn->Text = L"Send config";
			this->SendConfigBtn->UseVisualStyleBackColor = true;
			this->SendConfigBtn->Click += gcnew System::EventHandler(this, &Form1::SendConfigBtn_Click);
			// 
			// GetConfigBtn
			// 
			this->GetConfigBtn->Enabled = false;
			this->GetConfigBtn->Location = System::Drawing::Point(33, 450);
			this->GetConfigBtn->Name = L"GetConfigBtn";
			this->GetConfigBtn->Size = System::Drawing::Size(125, 23);
			this->GetConfigBtn->TabIndex = 2;
			this->GetConfigBtn->Text = L"Get config";
			this->GetConfigBtn->UseVisualStyleBackColor = true;
			this->GetConfigBtn->Click += gcnew System::EventHandler(this, &Form1::GetConfigBtn_Click);
			// 
			// StateLabel
			// 
			this->StateLabel->AutoSize = true;
			this->StateLabel->Enabled = false;
			this->StateLabel->Location = System::Drawing::Point(94, 18);
			this->StateLabel->Name = L"StateLabel";
			this->StateLabel->Size = System::Drawing::Size(84, 13);
			this->StateLabel->TabIndex = 3;
			this->StateLabel->Text = L"State: Unknown";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->TimerStepLength);
			this->groupBox1->Controls->Add(this->TimerFrequency);
			this->groupBox1->Controls->Add(this->StarDayLength);
			this->groupBox1->Controls->Add(this->label14);
			this->groupBox1->Controls->Add(this->IntervalCorrection);
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Controls->Add(this->DriverPulseWigth);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->DriverMicrostepCount);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->MotorStepCount);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->GearRatio);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->MainGearCogsCount);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(13, 42);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(308, 274);
			this->groupBox1->TabIndex = 25;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Parametrs";
			// 
			// TimerStepLength
			// 
			this->TimerStepLength->DecimalPlaces = 6;
			this->TimerStepLength->Enabled = false;
			this->TimerStepLength->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 393216});
			this->TimerStepLength->Location = System::Drawing::Point(164, 237);
			this->TimerStepLength->Name = L"TimerStepLength";
			this->TimerStepLength->Size = System::Drawing::Size(125, 20);
			this->TimerStepLength->TabIndex = 44;
			this->TimerStepLength->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// TimerFrequency
			// 
			this->TimerFrequency->Enabled = false;
			this->TimerFrequency->Location = System::Drawing::Point(164, 209);
			this->TimerFrequency->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {48000000, 0, 0, 0});
			this->TimerFrequency->Name = L"TimerFrequency";
			this->TimerFrequency->Size = System::Drawing::Size(125, 20);
			this->TimerFrequency->TabIndex = 42;
			this->TimerFrequency->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// StarDayLength
			// 
			this->StarDayLength->DecimalPlaces = 6;
			this->StarDayLength->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 393216});
			this->StarDayLength->Location = System::Drawing::Point(164, 27);
			this->StarDayLength->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {86400, 0, 0, 0});
			this->StarDayLength->Name = L"StarDayLength";
			this->StarDayLength->Size = System::Drawing::Size(125, 20);
			this->StarDayLength->TabIndex = 41;
			this->StarDayLength->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->StarDayLength->ValueChanged += gcnew System::EventHandler(this, &Form1::StarDayLength_ValueChanged);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(17, 239);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(92, 13);
			this->label14->TabIndex = 39;
			this->label14->Text = L"Step length, uSec";
			// 
			// IntervalCorrection
			// 
			this->IntervalCorrection->DecimalPlaces = 6;
			this->IntervalCorrection->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 393216});
			this->IntervalCorrection->Location = System::Drawing::Point(164, 183);
			this->IntervalCorrection->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {32767, 0, 0, 0});
			this->IntervalCorrection->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {32768, 0, 0, System::Int32::MinValue});
			this->IntervalCorrection->Name = L"IntervalCorrection";
			this->IntervalCorrection->Size = System::Drawing::Size(125, 20);
			this->IntervalCorrection->TabIndex = 38;
			this->IntervalCorrection->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->IntervalCorrection->ValueChanged += gcnew System::EventHandler(this, &Form1::StarDayLength_ValueChanged);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(17, 211);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(102, 13);
			this->label12->TabIndex = 27;
			this->label12->Text = L"Timer frequency, Hz";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(17, 185);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(92, 13);
			this->label10->TabIndex = 37;
			this->label10->Text = L"Interval correction";
			// 
			// DriverPulseWigth
			// 
			this->DriverPulseWigth->Location = System::Drawing::Point(164, 157);
			this->DriverPulseWigth->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->DriverPulseWigth->Name = L"DriverPulseWigth";
			this->DriverPulseWigth->Size = System::Drawing::Size(125, 20);
			this->DriverPulseWigth->TabIndex = 36;
			this->DriverPulseWigth->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->DriverPulseWigth->ValueChanged += gcnew System::EventHandler(this, &Form1::StarDayLength_ValueChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(17, 159);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(95, 13);
			this->label6->TabIndex = 35;
			this->label6->Text = L"Pulse width, uSec ";
			// 
			// DriverMicrostepCount
			// 
			this->DriverMicrostepCount->Location = System::Drawing::Point(164, 131);
			this->DriverMicrostepCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->DriverMicrostepCount->Name = L"DriverMicrostepCount";
			this->DriverMicrostepCount->Size = System::Drawing::Size(125, 20);
			this->DriverMicrostepCount->TabIndex = 34;
			this->DriverMicrostepCount->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->DriverMicrostepCount->ValueChanged += gcnew System::EventHandler(this, &Form1::StarDayLength_ValueChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(17, 133);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(83, 13);
			this->label5->TabIndex = 33;
			this->label5->Text = L"Microstep count";
			// 
			// MotorStepCount
			// 
			this->MotorStepCount->Location = System::Drawing::Point(164, 105);
			this->MotorStepCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->MotorStepCount->Name = L"MotorStepCount";
			this->MotorStepCount->Size = System::Drawing::Size(125, 20);
			this->MotorStepCount->TabIndex = 32;
			this->MotorStepCount->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->MotorStepCount->ValueChanged += gcnew System::EventHandler(this, &Form1::StarDayLength_ValueChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(17, 107);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(87, 13);
			this->label4->TabIndex = 31;
			this->label4->Text = L"Motor step count";
			// 
			// GearRatio
			// 
			this->GearRatio->Location = System::Drawing::Point(164, 79);
			this->GearRatio->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->GearRatio->Name = L"GearRatio";
			this->GearRatio->Size = System::Drawing::Size(125, 20);
			this->GearRatio->TabIndex = 30;
			this->GearRatio->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->GearRatio->ValueChanged += gcnew System::EventHandler(this, &Form1::StarDayLength_ValueChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(17, 81);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 13);
			this->label3->TabIndex = 29;
			this->label3->Text = L"Gear ratio";
			// 
			// MainGearCogsCount
			// 
			this->MainGearCogsCount->Location = System::Drawing::Point(164, 53);
			this->MainGearCogsCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->MainGearCogsCount->Name = L"MainGearCogsCount";
			this->MainGearCogsCount->Size = System::Drawing::Size(125, 20);
			this->MainGearCogsCount->TabIndex = 28;
			this->MainGearCogsCount->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			this->MainGearCogsCount->ValueChanged += gcnew System::EventHandler(this, &Form1::StarDayLength_ValueChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(17, 55);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 13);
			this->label2->TabIndex = 27;
			this->label2->Text = L"Main Gear Cogs";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(17, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(103, 13);
			this->label1->TabIndex = 26;
			this->label1->Text = L"Star day length, Sec";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->IntervalSteps);
			this->groupBox2->Controls->Add(this->PulseWidthSteps);
			this->groupBox2->Controls->Add(this->IntervalMicroSec);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->Interval);
			this->groupBox2->Location = System::Drawing::Point(13, 322);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(308, 111);
			this->groupBox2->TabIndex = 26;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Results";
			// 
			// IntervalSteps
			// 
			this->IntervalSteps->DecimalPlaces = 6;
			this->IntervalSteps->Enabled = false;
			this->IntervalSteps->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 393216});
			this->IntervalSteps->Location = System::Drawing::Point(164, 71);
			this->IntervalSteps->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {65535, 0, 0, 0});
			this->IntervalSteps->Name = L"IntervalSteps";
			this->IntervalSteps->Size = System::Drawing::Size(125, 20);
			this->IntervalSteps->TabIndex = 46;
			this->IntervalSteps->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// PulseWidthSteps
			// 
			this->PulseWidthSteps->DecimalPlaces = 6;
			this->PulseWidthSteps->Enabled = false;
			this->PulseWidthSteps->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 393216});
			this->PulseWidthSteps->Location = System::Drawing::Point(164, 45);
			this->PulseWidthSteps->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {65535, 0, 0, 0});
			this->PulseWidthSteps->Name = L"PulseWidthSteps";
			this->PulseWidthSteps->Size = System::Drawing::Size(125, 20);
			this->PulseWidthSteps->TabIndex = 45;
			this->PulseWidthSteps->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// IntervalMicroSec
			// 
			this->IntervalMicroSec->DecimalPlaces = 6;
			this->IntervalMicroSec->Enabled = false;
			this->IntervalMicroSec->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 393216});
			this->IntervalMicroSec->Location = System::Drawing::Point(164, 19);
			this->IntervalMicroSec->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {65535, 0, 0, 0});
			this->IntervalMicroSec->Name = L"IntervalMicroSec";
			this->IntervalMicroSec->Size = System::Drawing::Size(125, 20);
			this->IntervalMicroSec->TabIndex = 45;
			this->IntervalMicroSec->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(17, 21);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(73, 13);
			this->label16->TabIndex = 27;
			this->label16->Text = L"Interval, uSec";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(19, 47);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(90, 13);
			this->label7->TabIndex = 24;
			this->label7->Text = L"Pulse width, step ";
			// 
			// Interval
			// 
			this->Interval->AutoSize = true;
			this->Interval->Location = System::Drawing::Point(19, 73);
			this->Interval->Name = L"Interval";
			this->Interval->Size = System::Drawing::Size(73, 13);
			this->Interval->TabIndex = 23;
			this->Interval->Text = L"Interval, steps";
			// 
			// LoadConfigBtn
			// 
			this->LoadConfigBtn->Enabled = false;
			this->LoadConfigBtn->Location = System::Drawing::Point(33, 482);
			this->LoadConfigBtn->Name = L"LoadConfigBtn";
			this->LoadConfigBtn->Size = System::Drawing::Size(125, 23);
			this->LoadConfigBtn->TabIndex = 27;
			this->LoadConfigBtn->Text = L"Load config";
			this->LoadConfigBtn->UseVisualStyleBackColor = true;
			this->LoadConfigBtn->Click += gcnew System::EventHandler(this, &Form1::LoadConfigBtn_Click);
			// 
			// SaveConfigBtn
			// 
			this->SaveConfigBtn->Enabled = false;
			this->SaveConfigBtn->Location = System::Drawing::Point(177, 482);
			this->SaveConfigBtn->Name = L"SaveConfigBtn";
			this->SaveConfigBtn->Size = System::Drawing::Size(125, 23);
			this->SaveConfigBtn->TabIndex = 28;
			this->SaveConfigBtn->Text = L"Save config";
			this->SaveConfigBtn->UseVisualStyleBackColor = true;
			this->SaveConfigBtn->Click += gcnew System::EventHandler(this, &Form1::SaveConfigBtn_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(332, 525);
			this->Controls->Add(this->SaveConfigBtn);
			this->Controls->Add(this->LoadConfigBtn);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->StateLabel);
			this->Controls->Add(this->GetConfigBtn);
			this->Controls->Add(this->SendConfigBtn);
			this->Controls->Add(this->Connect_btn);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TimerStepLength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->TimerFrequency))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->StarDayLength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->IntervalCorrection))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DriverPulseWigth))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DriverMicrostepCount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MotorStepCount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->GearRatio))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MainGearCogsCount))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->IntervalSteps))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PulseWidthSteps))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->IntervalMicroSec))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Connect_btn_Click(System::Object^  sender, System::EventArgs^  e) {
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------BEGIN CUT AND PASTE BLOCK-----------------------------------------------------------------------------------
		/* 
		Before we can "connect" our application to our USB embedded device, we must first find the device.
		A USB bus can have many devices simultaneously connected, so somehow we have to find our device, and only
		our device.  This is done with the Vendor ID (VID) and Product ID (PID).  Each USB product line should have
		a unique combination of VID and PID.  

		Microsoft has created a number of functions which are useful for finding plug and play devices.  Documentation
		for each function used can be found in the MSDN library.  We will be using the following functions:

		SetupDiGetClassDevs()					//provided by setupapi.dll, which comes with Windows
		SetupDiEnumDeviceInterfaces()			//provided by setupapi.dll, which comes with Windows
		GetLastError()							//provided by kernel32.dll, which comes with Windows
		SetupDiDestroyDeviceInfoList()			//provided by setupapi.dll, which comes with Windows
		SetupDiGetDeviceInterfaceDetail()		//provided by setupapi.dll, which comes with Windows
		SetupDiGetDeviceRegistryProperty()		//provided by setupapi.dll, which comes with Windows
		malloc()								//part of C runtime library, msvcrt.dll?
		CreateFile()							//provided by kernel32.dll, which comes with Windows

		We will also be using the following unusual data types and structures.  Documentation can also be found in
		the MSDN library:

		PSP_DEVICE_INTERFACE_DATA
		PSP_DEVICE_INTERFACE_DETAIL_DATA
		SP_DEVINFO_DATA
		HDEVINFO
		HANDLE
		GUID

		The ultimate objective of the following code is to call CreateFile(), which opens a communications
		pipe to a specific device (such as a HID class USB device endpoint).  CreateFile() returns a "handle" 
		which is needed later when calling ReadFile() or WriteFile().  These functions are used to actually 
		send and receive application related data to/from the USB peripheral device.

		However, in order to call CreateFile(), we first need to get the device path for the USB device
		with the correct VID and PID.  Getting the device path is a multi-step round about process, which
		requires calling several of the SetupDixxx() functions provided by setupapi.dll.
		*/


		//Globally Unique Identifier (GUID) for HID class devices.  Windows uses GUIDs to identify things.
		GUID InterfaceClassGuid = {0x4d1e55b2, 0xf16f, 0x11cf, 0x88, 0xcb, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30}; 

		HDEVINFO DeviceInfoTable = INVALID_HANDLE_VALUE;
		PSP_DEVICE_INTERFACE_DATA InterfaceDataStructure = new SP_DEVICE_INTERFACE_DATA;
		PSP_DEVICE_INTERFACE_DETAIL_DATA DetailedInterfaceDataStructure = new SP_DEVICE_INTERFACE_DETAIL_DATA;
		SP_DEVINFO_DATA DevInfoData;

		DWORD InterfaceIndex = 0;
		DWORD StatusLastError = 0;
		DWORD dwRegType;
		DWORD dwRegSize;
		DWORD StructureSize = 0;
		PBYTE PropertyValueBuffer;
		bool MatchFound = false;
		DWORD ErrorStatus;

		String^ DeviceIDToFind = MY_DEVICE_ID;

		//First populate a list of plugged in devices (by specifying "DIGCF_PRESENT"), which are of the specified class GUID. 
		DeviceInfoTable = SetupDiGetClassDevsUM(&InterfaceClassGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

		//Now look through the list we just populated.  We are trying to see if any of them match our device. 
		while(true)
		{
			InterfaceDataStructure->cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
			if(SetupDiEnumDeviceInterfacesUM(DeviceInfoTable, NULL, &InterfaceClassGuid, InterfaceIndex, InterfaceDataStructure))
			{
				ErrorStatus = GetLastError();
				if(ERROR_NO_MORE_ITEMS == ErrorStatus)	//Did we reach the end of the list of matching devices in the DeviceInfoTable?
				{	//Cound not find the device.  Must not have been attached.
					SetupDiDestroyDeviceInfoListUM(DeviceInfoTable);	//Clean up the old structure we no longer need.
					return;		
				}
			}
			else	//Else some other kind of unknown error ocurred...
			{
				ErrorStatus = GetLastError();
				SetupDiDestroyDeviceInfoListUM(DeviceInfoTable);	//Clean up the old structure we no longer need.
				return;	
			}

			//Now retrieve the hardware ID from the registry.  The hardware ID contains the VID and PID, which we will then 
			//check to see if it is the correct device or not.

			//Initialize an appropriate SP_DEVINFO_DATA structure.  We need this structure for SetupDiGetDeviceRegistryProperty().
			DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
			SetupDiEnumDeviceInfoUM(DeviceInfoTable, InterfaceIndex, &DevInfoData);

			//First query for the size of the hardware ID, so we can know how big a buffer to allocate for the data.
			SetupDiGetDeviceRegistryPropertyUM(DeviceInfoTable, &DevInfoData, SPDRP_HARDWAREID, &dwRegType, NULL, 0, &dwRegSize);

			//Allocate a buffer for the hardware ID.
			PropertyValueBuffer = (BYTE *) malloc (dwRegSize);
			if(PropertyValueBuffer == NULL)	//if null, error, couldn't allocate enough memory
			{	//Can't really recover from this situation, just exit instead.
				SetupDiDestroyDeviceInfoListUM(DeviceInfoTable);	//Clean up the old structure we no longer need.
				return;		
			}

			//Retrieve the hardware IDs for the current device we are looking at.  PropertyValueBuffer gets filled with a 
			//REG_MULTI_SZ (array of null terminated strings).  To find a device, we only care about the very first string in the
			//buffer, which will be the "device ID".  The device ID is a string which contains the VID and PID, in the example 
			//format "Vid_04d8&Pid_003f".
			SetupDiGetDeviceRegistryPropertyUM(DeviceInfoTable, &DevInfoData, SPDRP_HARDWAREID, &dwRegType, PropertyValueBuffer, dwRegSize, NULL);

			//Now check if the first string in the hardware ID matches the device ID of my USB device.
			#ifdef UNICODE
			String^ DeviceIDFromRegistry = gcnew String((wchar_t *)PropertyValueBuffer);
			#else
			String^ DeviceIDFromRegistry = gcnew String((char *)PropertyValueBuffer);
			#endif

			free(PropertyValueBuffer);		//No longer need the PropertyValueBuffer, free the memory to prevent potential memory leaks

			//Convert both strings to lower case.  This makes the code more robust/portable accross OS Versions
			DeviceIDFromRegistry = DeviceIDFromRegistry->ToLowerInvariant();	
			DeviceIDToFind = DeviceIDToFind->ToLowerInvariant();				
			//Now check if the hardware ID we are looking at contains the correct VID/PID
			MatchFound = DeviceIDFromRegistry->Contains(DeviceIDToFind);		
			if(MatchFound == true)
			{
				//Device must have been found.  Open read and write handles.  In order to do this, we will need the actual device path first.
				//We can get the path by calling SetupDiGetDeviceInterfaceDetail(), however, we have to call this function twice:  The first
				//time to get the size of the required structure/buffer to hold the detailed interface data, then a second time to actually 
				//get the structure (after we have allocated enough memory for the structure.)
				DetailedInterfaceDataStructure->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
				//First call populates "StructureSize" with the correct value
				SetupDiGetDeviceInterfaceDetailUM(DeviceInfoTable, InterfaceDataStructure, NULL, NULL, &StructureSize, NULL);	
				DetailedInterfaceDataStructure = (PSP_DEVICE_INTERFACE_DETAIL_DATA)(malloc(StructureSize));		//Allocate enough memory
				if(DetailedInterfaceDataStructure == NULL)	//if null, error, couldn't allocate enough memory
				{	//Can't really recover from this situation, just exit instead.
					SetupDiDestroyDeviceInfoListUM(DeviceInfoTable);	//Clean up the old structure we no longer need.
					return;		
				}
				DetailedInterfaceDataStructure->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
				 //Now call SetupDiGetDeviceInterfaceDetail() a second time to receive the goods.  
				SetupDiGetDeviceInterfaceDetailUM(DeviceInfoTable, InterfaceDataStructure, DetailedInterfaceDataStructure, StructureSize, NULL, NULL); 

				//We now have the proper device path, and we can finally open read and write handles to the device.
				//We store the handles in the global variables "WriteHandle" and "ReadHandle", which we will use later to actually communicate.
				WriteHandle = CreateFile((DetailedInterfaceDataStructure->DevicePath), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);

				ErrorStatus = GetLastError();
				if(ErrorStatus == ERROR_SUCCESS)
				{
					SendConfigBtn->Enabled = true;
					SaveConfigBtn->Enabled = true;
					StateLabel->Text = "Device connected.";
				}
				ReadHandle = CreateFile((DetailedInterfaceDataStructure->DevicePath), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
				ErrorStatus = GetLastError();
				if(ErrorStatus == ERROR_SUCCESS)
				{
					GetConfigBtn->Enabled = true;
					LoadConfigBtn->Enabled = true;
					StateLabel->Enabled = true;					//Make label no longer greyed out
					StateLabel->Text = "Device connected.";
				}
				SetupDiDestroyDeviceInfoListUM(DeviceInfoTable);	//Clean up the old structure we no longer need.
				return;
			}

			InterfaceIndex++;	
			//Keep looping until we either find a device with matching VID and PID, or until we run out of items.
		}//end of while(true)	
//-------------------------------------------------------END CUT AND PASTE BLOCK-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
			 }


private: System::Void SendConfigBtn_Click(System::Object^  sender, System::EventArgs^  e) {
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------BEGIN CUT AND PASTE BLOCK-----------------------------------------------------------------------------------
		 DWORD BytesWritten = 0;
		 unsigned char OutputPacketBuffer[65];	//Allocate a memory buffer equal to our endpoint size + 1
		 APP_CONFIG AppConfig;

		 OutputPacketBuffer[0] = 0;			//The first byte is the "Report ID".  This number is used by the USB driver, but does not
											//get tranmitted accross the USB bus.  The custom HID class firmware is only configured for
											//one type of report, therefore, we must always initializate this byte to "0" before sending
											//a data packet to the device.

		 OutputPacketBuffer[1] = COMMAND_SET_CONFIG;		//0x80 is the "Toggle LED(s)" command in the firmware
											//For simplicity, we will leave the rest of the buffer uninitialized, but you could put real
											//data in it if you like.
		 GetParams(&AppConfig);
	     		 
		 OutputPacketBuffer[2] = AppConfig.MainGearCogsCount & 0xFF;
		 OutputPacketBuffer[3] = AppConfig.MainGearCogsCount >> 8;
		 OutputPacketBuffer[4] = AppConfig.GearRatio & 0xFF;
		 OutputPacketBuffer[5] = AppConfig.GearRatio >> 8;
		 OutputPacketBuffer[6] = AppConfig.SM_StepCount & 0xFF;
		 OutputPacketBuffer[7] = AppConfig.SM_StepCount >> 8;
		 OutputPacketBuffer[8] = AppConfig.SM_uStepCount & 0xFF;
		 OutputPacketBuffer[9] = AppConfig.SM_uStepCount >> 8;
		 OutputPacketBuffer[10] = AppConfig.IntervalCorrection & 0xFF;
		 OutputPacketBuffer[11] = AppConfig.IntervalCorrection >> 8;
		 
		 OutputPacketBuffer[12] = AppConfig.IntervalCorrection_1kk & 0xFF;
		 OutputPacketBuffer[13] = (AppConfig.IntervalCorrection_1kk >> 8) & 0xFF;
		 OutputPacketBuffer[14] = (AppConfig.IntervalCorrection_1kk >> 16) & 0xFF;
		 OutputPacketBuffer[15] = (AppConfig.IntervalCorrection_1kk >> 24) & 0xFF;
		 
		 OutputPacketBuffer[16] = AppConfig.PulseWidth & 0xFF;
		 OutputPacketBuffer[17] = AppConfig.PulseWidth >> 8;

		 OutputPacketBuffer[18] = AppConfig.TimerFrequency & 0xFF;
		 OutputPacketBuffer[19] = (AppConfig.TimerFrequency >> 8) & 0xFF;
		 OutputPacketBuffer[20] = (AppConfig.TimerFrequency >> 16) & 0xFF;
		 OutputPacketBuffer[21] = (AppConfig.TimerFrequency >> 24) & 0xFF;

		 OutputPacketBuffer[22] = AppConfig.Interval & 0xFF;
		 OutputPacketBuffer[23] = AppConfig.Interval >> 8;

		 OutputPacketBuffer[24] = AppConfig.Interval_1kk & 0xFF;
		 OutputPacketBuffer[25] = (AppConfig.Interval_1kk >> 8) & 0xFF;
		 OutputPacketBuffer[26] = (AppConfig.Interval_1kk >> 16) & 0xFF;
		 OutputPacketBuffer[27] = (AppConfig.Interval_1kk >> 24) & 0xFF;

		 OutputPacketBuffer[28] = AppConfig.StarDayLength & 0xFF;
		 OutputPacketBuffer[29] = (AppConfig.StarDayLength >> 8) & 0xFF;
		 OutputPacketBuffer[30] = (AppConfig.StarDayLength >> 16) & 0xFF;
		 OutputPacketBuffer[31] = (AppConfig.StarDayLength >> 24) & 0xFF;

		 OutputPacketBuffer[32] = AppConfig.StarDayLength_1kk & 0xFF;
		 OutputPacketBuffer[33] = (AppConfig.StarDayLength_1kk >> 8) & 0xFF;
		 OutputPacketBuffer[34] = (AppConfig.StarDayLength_1kk >> 16) & 0xFF;
		 OutputPacketBuffer[35] = (AppConfig.StarDayLength_1kk >> 24) & 0xFF;

		 //The basic Windows I/O functions WriteFile() and ReadFile() can be used to read and write to HID class USB devices.
		 //Note that we need the handle which we got earlier when we called CreateFile() (when we hit the connect button).
		 //The following function call will send out 64 bytes (starting from OutputPacketBuffer[1]) to the USB device.  The data will
		 //arrive on the OUT interrupt endpoint.
		 WriteFile(WriteHandle, &OutputPacketBuffer, 65, &BytesWritten, 0);	//Blocking function, unless an "overlapped" structure is used
		 StateLabel->Text = "Current config temporary changed.";
//-------------------------------------------------------END CUT AND PASTE BLOCK-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
		 }


private: System::Void GetConfigBtn_Click(System::Object^  sender, System::EventArgs^  e) {
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------BEGIN CUT AND PASTE BLOCK-----------------------------------------------------------------------------------
		 DWORD BytesWritten = 0;
		 DWORD BytesRead = 0;
		 unsigned char OutputPacketBuffer[65];	//Allocate a memory buffer equal to our endpoint size + 1
		 unsigned char InputPacketBuffer[65];	//Allocate a memory buffer equal to our endpoint size + 1
		 APP_CONFIG AppConfig;

		 InputPacketBuffer[0] = 0;				//The first byte is the "Report ID" and does not get transmitted over the USB bus.  Always set = 0.
		 OutputPacketBuffer[0] = 0;				//The first byte is the "Report ID" and does not get transmitted over the USB bus.  Always set = 0.

		 OutputPacketBuffer[1] = COMMAND_GET_CONFIG;			//0x81 is the "Get Pushbutton State" command in the firmware
												//For simplicity, we will leave the rest of the buffer uninitialized, but you could put real
												//data in it if you like.

		 //The basic Windows I/O functions WriteFile() and ReadFile() can be used to read and write to HID class USB devices 
		 //(once we have the read and write handles to the device, which are obtained with CreateFile()).

		 //To get the pushbutton state, first, we send a packet with our "Get Pushbutton State" command in it.
		 //The following call to WriteFile() sends 64 bytes of data to the USB device.
		 WriteFile(WriteHandle, &OutputPacketBuffer, 65, &BytesWritten, 0);	//Blocking function, unless an "overlapped" structure is used
		 //Now get the response packet from the firmware.
		 //The following call to ReadFIle() retrieves 64 bytes of data from the USB device.
		 ReadFile(ReadHandle, &InputPacketBuffer, 65, &BytesRead, 0);		//Blocking function, unless an "overlapped" structure is used	

		 //InputPacketBuffer[0] is the report ID, which we don't care about.
		 //InputPacketBuffer[1] is an echo back of the command.
		 //InputPacketBuffer[2] contains the I/O port pin value for the pushbutton.  
		 BYTE * p = &InputPacketBuffer[2];
		 int i = 2;
		 memset(&AppConfig, 0, sizeof(AppConfig));
		 //memcpy(&AppConfig,p,sizeof(AppConfig));
		 
 		 AppConfig.MainGearCogsCount = InputPacketBuffer[2] + (InputPacketBuffer[3] << 8);
 		 AppConfig.GearRatio = InputPacketBuffer[4] + (InputPacketBuffer[5] << 8);
 		 AppConfig.SM_StepCount = InputPacketBuffer[6] + (InputPacketBuffer[7] << 8);
 		 AppConfig.SM_uStepCount = InputPacketBuffer[8] + (InputPacketBuffer[9] << 8);
 		 AppConfig.IntervalCorrection = InputPacketBuffer[10] + (InputPacketBuffer[11] << 8);
 		 AppConfig.IntervalCorrection_1kk = InputPacketBuffer[12] + (InputPacketBuffer[13] << 8) + (InputPacketBuffer[14]<<16) + (InputPacketBuffer[15] << 24);
 		 AppConfig.PulseWidth = InputPacketBuffer[16] + (InputPacketBuffer[17] << 8);
		 AppConfig.TimerFrequency = InputPacketBuffer[18] + (InputPacketBuffer[19] << 8) + (InputPacketBuffer[20]<<16) + (InputPacketBuffer[21] << 24);
 		 AppConfig.Interval = InputPacketBuffer[22] + (InputPacketBuffer[23] << 8);
 		 AppConfig.Interval_1kk = InputPacketBuffer[24] + (InputPacketBuffer[25] << 8) + (InputPacketBuffer[26]<<16) + (InputPacketBuffer[27] << 24);
		 AppConfig.StarDayLength = InputPacketBuffer[28] + (InputPacketBuffer[29] << 8) + (InputPacketBuffer[30]<<16) + (InputPacketBuffer[31] << 24);
		 AppConfig.StarDayLength_1kk = InputPacketBuffer[32] + (InputPacketBuffer[33] << 8) + (InputPacketBuffer[34]<<16) + (InputPacketBuffer[35] << 24);

		 NeedUpdate = false;
		 SetParams(&AppConfig, true);
		 NeedUpdate = true;
		 StateLabel->Text = "Current config received.";
//-------------------------------------------------------END CUT AND PASTE BLOCK-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

		 }		 
private: System::Void StarDayLength_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(NeedUpdate){
				APP_CONFIG AppConfig;			
				GetParams(&AppConfig);
				SetParams(&AppConfig, false);
			 }
		}
	void CalculateParam(APP_CONFIG * config){
		 double step_per_grad = (double)config->TimerFrequency / (double)(config->SM_StepCount * config->SM_uStepCount * config->GearRatio);
		 double Star_Day_Length = ((double)config->StarDayLength_1kk / 1000000.0) + (double) config->StarDayLength;
		 double Interval = (Star_Day_Length / 360.0) * step_per_grad;
		 config->Interval = (uint16_t)Interval;
		 config->Interval_1kk = (uint32_t)((Interval - (double)config->Interval)* 1000000.0);

	}
	void SetParams(APP_CONFIG * config, bool FullUpdate) {
		CalculateParam(config);
		if(FullUpdate){
			double Temp = ((double)config->StarDayLength_1kk / 1000000.0) + (double)config->StarDayLength;
			StarDayLength->Value = Decimal(Temp);
			MainGearCogsCount->Value = config->MainGearCogsCount;
			GearRatio->Value = config->GearRatio;
			MotorStepCount->Value = config->SM_StepCount;
			DriverMicrostepCount->Value = config->SM_uStepCount;
			DriverPulseWigth->Value = config->PulseWidth;			
			IntervalCorrection->Value = Decimal(((double)config->IntervalCorrection_1kk / 1000000.0) + (double)config->IntervalCorrection);
			TimerFrequency->Value = (UInt32)config->TimerFrequency;		 
			TimerStepLength->Value = Decimal((1000000.0/(double)config->TimerFrequency));
		}
		double Interval = ((double)config->Interval_1kk / 1000000.0) + (double)config->Interval;
		IntervalMicroSec->Value = Decimal( Interval/(double)config->TimerFrequency);
		PulseWidthSteps->Value = Decimal((double)config->PulseWidth/(double)config->TimerFrequency);
		IntervalSteps->Value = Decimal(Interval);
		
	}
	void GetParams(APP_CONFIG * config) {
		double Temp = 0.0;
		Temp = (double)StarDayLength->Value;
		config->StarDayLength = (uint32_t)Temp;
		config->StarDayLength_1kk = (uint32_t)((Temp - (double)config->StarDayLength)* 1000000.0);
		config->MainGearCogsCount = (uint16_t)MainGearCogsCount->Value;
		config->GearRatio = (uint16_t)GearRatio->Value;
		config->SM_StepCount = (uint16_t)MotorStepCount->Value;
		config->SM_uStepCount = (uint16_t)DriverMicrostepCount->Value;
		config->PulseWidth = (uint16_t)DriverPulseWigth->Value;
		Temp = (double)IntervalCorrection->Value;
		config->IntervalCorrection = (int16_t)Temp;
		config->IntervalCorrection_1kk = (int32_t)((Temp - (double)config->IntervalCorrection)* 1000000.0);
		config->TimerFrequency = (UInt32)TimerFrequency->Value;
		CalculateParam(config);
	}
private: System::Void LoadConfigBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 DWORD BytesWritten = 0;
			 DWORD BytesRead = 0;
			 unsigned char OutputPacketBuffer[65];	//Allocate a memory buffer equal to our endpoint size + 1
			 unsigned char InputPacketBuffer[65];	//Allocate a memory buffer equal to our endpoint size + 1
			 APP_CONFIG AppConfig;

			 InputPacketBuffer[0] = 0;				//The first byte is the "Report ID" and does not get transmitted over the USB bus.  Always set = 0.
			 OutputPacketBuffer[0] = 0;				//The first byte is the "Report ID" and does not get transmitted over the USB bus.  Always set = 0.

			 OutputPacketBuffer[1] = COMMAND_LOAD_CONFIG;			//0x81 is the "Get Pushbutton State" command in the firmware
			 //For simplicity, we will leave the rest of the buffer uninitialized, but you could put real
			 //data in it if you like.

			 //The basic Windows I/O functions WriteFile() and ReadFile() can be used to read and write to HID class USB devices 
			 //(once we have the read and write handles to the device, which are obtained with CreateFile()).

			 //To get the pushbutton state, first, we send a packet with our "Get Pushbutton State" command in it.
			 //The following call to WriteFile() sends 64 bytes of data to the USB device.
			 WriteFile(WriteHandle, &OutputPacketBuffer, 65, &BytesWritten, 0);	//Blocking function, unless an "overlapped" structure is used
			 //Now get the response packet from the firmware.
			 //The following call to ReadFIle() retrieves 64 bytes of data from the USB device.
			 ReadFile(ReadHandle, &InputPacketBuffer, 65, &BytesRead, 0);		//Blocking function, unless an "overlapped" structure is used	

			 //InputPacketBuffer[0] is the report ID, which we don't care about.
			 //InputPacketBuffer[1] is an echo back of the command.
			 //InputPacketBuffer[2] contains the I/O port pin value for the pushbutton.  
			 BYTE * p = &InputPacketBuffer[2];
			 int i = 2;
			 memset(&AppConfig, 0, sizeof(AppConfig));
			 //memcpy(&AppConfig,p,sizeof(AppConfig));

			 AppConfig.MainGearCogsCount = InputPacketBuffer[2] + (InputPacketBuffer[3] << 8);
			 AppConfig.GearRatio = InputPacketBuffer[4] + (InputPacketBuffer[5] << 8);
			 AppConfig.SM_StepCount = InputPacketBuffer[6] + (InputPacketBuffer[7] << 8);
			 AppConfig.SM_uStepCount = InputPacketBuffer[8] + (InputPacketBuffer[9] << 8);
			 AppConfig.IntervalCorrection = InputPacketBuffer[10] + (InputPacketBuffer[11] << 8);
			 AppConfig.IntervalCorrection_1kk = InputPacketBuffer[12] + (InputPacketBuffer[13] << 8) + (InputPacketBuffer[14]<<16) + (InputPacketBuffer[15] << 24);
			 AppConfig.PulseWidth = InputPacketBuffer[16] + (InputPacketBuffer[17] << 8);
			 AppConfig.TimerFrequency = InputPacketBuffer[18] + (InputPacketBuffer[19] << 8) + (InputPacketBuffer[20]<<16) + (InputPacketBuffer[21] << 24);
			 AppConfig.Interval = InputPacketBuffer[22] + (InputPacketBuffer[23] << 8);
			 AppConfig.Interval_1kk = InputPacketBuffer[24] + (InputPacketBuffer[25] << 8) + (InputPacketBuffer[26]<<16) + (InputPacketBuffer[27] << 24);
			 AppConfig.StarDayLength = InputPacketBuffer[28] + (InputPacketBuffer[29] << 8) + (InputPacketBuffer[30]<<16) + (InputPacketBuffer[31] << 24);
			 AppConfig.StarDayLength_1kk = InputPacketBuffer[32] + (InputPacketBuffer[33] << 8) + (InputPacketBuffer[34]<<16) + (InputPacketBuffer[35] << 24);

			 NeedUpdate = false;
			 SetParams(&AppConfig, true);
			 NeedUpdate = true;
			 StateLabel->Text = "Config loaded from memory.";
		 }
private: System::Void SaveConfigBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 //-------------------------------------------------------------------------------------------------------------------------------------------------------------------
			 //-------------------------------------------------------BEGIN CUT AND PASTE BLOCK-----------------------------------------------------------------------------------
			 DWORD BytesWritten = 0;
			 unsigned char OutputPacketBuffer[65];	//Allocate a memory buffer equal to our endpoint size + 1
			 APP_CONFIG AppConfig;

			 OutputPacketBuffer[0] = 0;			//The first byte is the "Report ID".  This number is used by the USB driver, but does not
			 //get tranmitted accross the USB bus.  The custom HID class firmware is only configured for
			 //one type of report, therefore, we must always initializate this byte to "0" before sending
			 //a data packet to the device.

			 OutputPacketBuffer[1] = COMMAND_SAVE_CONFIG;		//0x80 is the "Toggle LED(s)" command in the firmware
			 //For simplicity, we will leave the rest of the buffer uninitialized, but you could put real
			 //data in it if you like.
			 GetParams(&AppConfig);

			 OutputPacketBuffer[2] = AppConfig.MainGearCogsCount & 0xFF;
			 OutputPacketBuffer[3] = AppConfig.MainGearCogsCount >> 8;
			 OutputPacketBuffer[4] = AppConfig.GearRatio & 0xFF;
			 OutputPacketBuffer[5] = AppConfig.GearRatio >> 8;
			 OutputPacketBuffer[6] = AppConfig.SM_StepCount & 0xFF;
			 OutputPacketBuffer[7] = AppConfig.SM_StepCount >> 8;
			 OutputPacketBuffer[8] = AppConfig.SM_uStepCount & 0xFF;
			 OutputPacketBuffer[9] = AppConfig.SM_uStepCount >> 8;
			 OutputPacketBuffer[10] = AppConfig.IntervalCorrection & 0xFF;
			 OutputPacketBuffer[11] = AppConfig.IntervalCorrection >> 8;

			 OutputPacketBuffer[12] = AppConfig.IntervalCorrection_1kk & 0xFF;
			 OutputPacketBuffer[13] = (AppConfig.IntervalCorrection_1kk >> 8) & 0xFF;
			 OutputPacketBuffer[14] = (AppConfig.IntervalCorrection_1kk >> 16) & 0xFF;
			 OutputPacketBuffer[15] = (AppConfig.IntervalCorrection_1kk >> 24) & 0xFF;

			 OutputPacketBuffer[16] = AppConfig.PulseWidth & 0xFF;
			 OutputPacketBuffer[17] = AppConfig.PulseWidth >> 8;

			 OutputPacketBuffer[18] = AppConfig.TimerFrequency & 0xFF;
			 OutputPacketBuffer[19] = (AppConfig.TimerFrequency >> 8) & 0xFF;
			 OutputPacketBuffer[20] = (AppConfig.TimerFrequency >> 16) & 0xFF;
			 OutputPacketBuffer[21] = (AppConfig.TimerFrequency >> 24) & 0xFF;

			 OutputPacketBuffer[22] = AppConfig.Interval & 0xFF;
			 OutputPacketBuffer[23] = AppConfig.Interval >> 8;

			 OutputPacketBuffer[24] = AppConfig.Interval_1kk & 0xFF;
			 OutputPacketBuffer[25] = (AppConfig.Interval_1kk >> 8) & 0xFF;
			 OutputPacketBuffer[26] = (AppConfig.Interval_1kk >> 16) & 0xFF;
			 OutputPacketBuffer[27] = (AppConfig.Interval_1kk >> 24) & 0xFF;

			 OutputPacketBuffer[28] = AppConfig.StarDayLength & 0xFF;
			 OutputPacketBuffer[29] = (AppConfig.StarDayLength >> 8) & 0xFF;
			 OutputPacketBuffer[30] = (AppConfig.StarDayLength >> 16) & 0xFF;
			 OutputPacketBuffer[31] = (AppConfig.StarDayLength >> 24) & 0xFF;

			 OutputPacketBuffer[32] = AppConfig.StarDayLength_1kk & 0xFF;
			 OutputPacketBuffer[33] = (AppConfig.StarDayLength_1kk >> 8) & 0xFF;
			 OutputPacketBuffer[34] = (AppConfig.StarDayLength_1kk >> 16) & 0xFF;
			 OutputPacketBuffer[35] = (AppConfig.StarDayLength_1kk >> 24) & 0xFF;

			 //The basic Windows I/O functions WriteFile() and ReadFile() can be used to read and write to HID class USB devices.
			 //Note that we need the handle which we got earlier when we called CreateFile() (when we hit the connect button).
			 //The following function call will send out 64 bytes (starting from OutputPacketBuffer[1]) to the USB device.  The data will
			 //arrive on the OUT interrupt endpoint.
			 WriteFile(WriteHandle, &OutputPacketBuffer, 65, &BytesWritten, 0);	//Blocking function, unless an "overlapped" structure is used
			 StateLabel->Text = "Config saved to memory.";
		 }
};
}


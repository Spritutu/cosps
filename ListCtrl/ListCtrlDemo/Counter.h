#ifndef _COUNTER_H_
#define _COUNTER_H_

#include "FileParser.h"

class CCounter
{
public:
	static UINT CountThreadProc(LPVOID lpvData);
};

class CProgressChecker : public CCancelledChecker
{
public:
	CProgressChecker(HWND hProgWnd);
	BOOL IsCancelled();
	void Reset();
private:
	HWND m_hProgWnd;
	CTimeCost m_timeCost;
};

class CFileCountVisitor : public CFileVisitor
{
public:
	CFileCountVisitor(HWND hWnd);
	virtual int VisitFile(LPCTSTR lpszFileName, LPVOID lpParam = NULL);
	virtual UINT GetResult() { return m_nCount; }
private:
	HWND m_hProgWnd;
	UINT m_nCount;
	CTimeCost m_timeCost;
};

class CFileParserVisitor : public CFileVisitor
{
public:
	CFileParserVisitor(HWND hMainWnd, HWND hProgressWnd);
	virtual int VisitFile(LPCTSTR lpszFileName, LPVOID lpParam = NULL);
	virtual UINT GetResult() { return m_nCount; }
	IFileParser* GetFileParser(int nLangRuleType, CFileInfo* pFileInfo, DWORD nMode = FP_MODE_DEFAULT);
protected:
	HWND m_hMainWnd;
	HWND m_hProgWnd;
	UINT m_nCount;
};

class CEvaluationFileParserVisitor : public CFileParserVisitor
{
public:
	CEvaluationFileParserVisitor(HWND hMainWnd, HWND hProgressWnd);
	virtual int VisitFile(LPCTSTR lpszFileName, LPVOID lpParam = NULL);
};

#endif
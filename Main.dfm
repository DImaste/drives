object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'NTFS Shark'
  ClientHeight = 423
  ClientWidth = 818
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PathEdit: TLabeledEdit
    Left = 8
    Top = 24
    Width = 449
    Height = 21
    EditLabel.Width = 155
    EditLabel.Height = 13
    EditLabel.Caption = #1055#1091#1090#1100' '#1082' '#1080#1084#1077#1085#1080' '#1092#1072#1081#1083#1072' ('#1088#1072#1079#1076#1077#1083#1072')'
    TabOrder = 0
    Text = '\\.\C:'
  end
  object ResultTree: TVirtualStringTree
    Left = 488
    Top = 105
    Width = 321
    Height = 296
    Header.AutoSizeIndex = 0
    Header.Font.Charset = DEFAULT_CHARSET
    Header.Font.Color = clWindowText
    Header.Font.Height = -11
    Header.Font.Name = 'Tahoma'
    Header.Font.Style = []
    Header.MainColumn = -1
    TabOrder = 1
    Columns = <>
  end
  object SearchButton: TButton
    Left = 288
    Top = 62
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 2
    OnClick = SearchButtonClick
  end
  object Television: TListBox
    Left = 8
    Top = 105
    Width = 449
    Height = 296
    ItemHeight = 13
    TabOrder = 3
  end
  object ReadBuffer: TButton
    Left = 376
    Top = 62
    Width = 81
    Height = 25
    Caption = #1063#1090#1077#1085#1080#1077
    TabOrder = 4
    OnClick = ReadBufferClick
  end
  object ByteEdit: TLabeledEdit
    Left = 8
    Top = 64
    Width = 193
    Height = 21
    EditLabel.Width = 173
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1083#1080#1095#1082#1089#1090#1074#1086' '#1073#1072#1081#1090' '#1076#1083#1103' '#1089#1095#1080#1090#1099#1074#1072#1085#1080#1103
    TabOrder = 5
    Text = '2'
  end
  object LogBox: TListBox
    Left = 488
    Top = 8
    Width = 322
    Height = 91
    ItemHeight = 13
    TabOrder = 6
  end
end

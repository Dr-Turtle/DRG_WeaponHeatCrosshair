#!/bin/bash
ProjectFolder=/home/turtle/Documents/Git/DRG/DRG_WeaponHeatCrosshair
UnrealPak=/home/turtle/Documents/UnrealEngine/Engine/Binaries/Linux/UnrealPak
UE4Editor=/home/turtle/Documents/UnrealEngine/Engine/Binaries/Linux/UE4Editor-Cmd
DRG='/home/turtle/.local/share/Steam/steamapps/common/Deep Rock Galactic'
ModName='test'
cd $ProjectFolder

$UE4Editor $ProjectFolder/FSD.uproject -run=cook -targetplatform=LinuxNoEditor

rm -r $ProjectFolder/packing/temp/*
cp -r $ProjectFolder/Saved/Cooked/LinuxNoEditor/FSD/Content/ $ProjectFolder/packing/temp/
cp $ProjectFolder/Saved/Cooked/LinuxNoEditor/FSD/AssetRegistry.bin $ProjectFolder/packing/temp/
rm $ProjectFolder/packing/$ModName.pak

touch $ProjectFolder/packing/input.txt
echo \"$ProjectFolder/packing/temp/\*\" \"'../../../FSD/'\" > $ProjectFolder/packing/input.txt
$UnrealPak $ProjectFolder/packing/test.pak -Create=$ProjectFolder/packing/input.txt

rm "$DRG/FSD/Mods/$ModName/$ModName.pak"
mkdir "$DRG/FSD/Mods/$ModName/"
cp $ProjectFolder/packing/$ModName.pak "$DRG/FSD/Mods/$ModName/"

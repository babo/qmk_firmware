package main

import (
    "encoding/json"
    "fmt"
    "hash/crc64"
    "io/ioutil"
    "os"
    "path/filepath"
    "sort"
    "strings"
    //"encoding/base64"
)

func main() {
    // Show Usage
    if len(os.Args) < 3 {
        fmt.Println("Usage: ./keymap-gen src-dir out-dir")
        fmt.Println("Outputs c files in out-dir")
        fmt.Println("Make sure the dirs exist.")
        return
    }

    files, err := filepath.Glob(os.Args[1] + "/*.json")
    if err != nil {
        fmt.Printf("Could not open src-dir: %v\n", err)
        return
    }

    for _, fname := range files {
        fmt.Println("Processing: ", fname)
        // Read the source
        data, err := ioutil.ReadFile(fname)
        if err != nil {
            panic(err)
        }

        // Unbundle Data
        var FullDict map[string]Entry
        json.Unmarshal(data, &FullDict)

        // Loop over entries and store
        var output []string
        for i, v := range FullDict {
            if i == "0" {
                continue
            }

            // Special handling for numbermap
            var entry string
            if strings.Contains(fname, "num") {
                entry = v.toKeymap("NUM|")
            } else {
                entry = v.toKeymap("")
            }

            if entry != "" {
                output = append(output, entry)
            }
        }

        // Sort by length, then amount of whitespace lol
        sort.Slice(output, func(i, j int) bool {
            var maxLen int
            if len(output[i]) > len(output[j]) {
                maxLen = len(output[i])
            } else {
                maxLen = len(output[j])
            }

            return maxLen-strings.Count(output[i][:40], " ") < maxLen-strings.Count(output[j][:40], " ")
        })

        // Whack a disclaimer
        output = append([]string{"// This file is automatically generated. Do not edit it!\n\n"}, output...)

        // Write all data out
        outName := filepath.Base(fname)
        outName = os.Args[2] + outName[:len(outName)-5] + ".def"
        fmt.Println("Saving: ", outName)
        ioutil.WriteFile(outName, []byte(strings.Join(output, "")), 0755)
    }
}

func (e Entry) toKeymap(prefix string) string {
    // storage for parts
    var command, chord, arg string
    wordInfo := parseWords(e)

    // Handle prefix
    if prefix != "" {
        chord = prefix
    }

    // Format the chord
    keys := []string{"AA", "AS", "AE", "AT", "AN", "AI", "AO", "AP"}
    for i, v := range e.Input {
        chord += keys[v-1]

        if i != len(e.Input)-1 {
            chord += "|"
        }
    }

    // Handle specials/base first
    var ok bool
    var v []string

    if e.Special != "" {
        v, ok = QMKLookup[e.Special]
    }
    if !ok && e.Base != "" {
        v, ok = QMKLookup[e.Base]
    }

    if ok {
        // Determine way to send key
        if len(v) == 1 {
            command = "PRES("
        } else {
            command = "KEYS("
        }
    }

    if ok {
        if len(v) > 1 {
            arg += "{"
        }

        // String together args
        for ii, vv := range v {
            arg += vv
            if ii == len(v)-1 && len(v) > 1 {
                arg += ", COMBO_END}"
            } else if ii != len(v)-1 {
                arg += ", "
            }
        }

        hash := crc64.Checksum([]byte(fmt.Sprintf("%v%v", arg, chord)), crc64.MakeTable(crc64.ECMA))
        hashStr := fmt.Sprintf("cmb_%x", hash)
        wordSpacer := strings.Repeat(" ", 42-len(arg))
        if command == "KEYS(" {
            arg = fmt.Sprintf("%v, %v %v", hashStr, wordSpacer, arg)
        } else {
            arg = fmt.Sprintf("%65v", arg)
        }

        goto Found
    }

    // Parse out word info
    if wordInfo.LRank == 0 && wordInfo.RRank == 0 {
        goto Blank
    }

    if wordInfo.LRank != 0 || wordInfo.RRank != 0 {
        if wordInfo.LRank != 0 && wordInfo.RRank != 0 {
            // Just blank the structure and recall
            left, right := e, e
            left.Trw = nil
            right.Tlw = nil
            return fmt.Sprintf("%v%v", left.toKeymap("LFT|"), right.toKeymap("RGT|"))
        }

        var word string
        if wordInfo.LRank > wordInfo.RRank {
            word = wordInfo.LWord
        } else {
            word = wordInfo.RWord
        }

        // Add in thumb
        chord = "AR|" + chord

        // generate function name
        hash := crc64.Checksum([]byte(word), crc64.MakeTable(crc64.ECMA))
        hashStr := fmt.Sprintf("str_%016X", hash)
        command = "SUBS("
        wordSpacer := strings.Repeat(" ", 40-len(word))
        arg = fmt.Sprintf("%v, %v \"%v \"", hashStr, wordSpacer, word)
        goto Found
    }

    panic(e.String())

Found:
    chord += ","
    return fmt.Sprintf("%v%-35v%v)\n", command, chord, arg)

Blank:
    return ""
}

type Entry struct {
    Input   []int
    Base    string
    Tlw     []interface{}
    Trw     []interface{}
    Special string
}
type Word struct {
    LWord string
    LRank float64
    RWord string
    RRank float64
}

func parseWords(e Entry) (ret Word) {
    if len(e.Tlw) > 0 {
        ret.LWord = e.Tlw[0].(string)
        ret.LRank = e.Tlw[1].(float64)
    }
    if len(e.Trw) > 0 {
        ret.RWord = e.Trw[0].(string)
        ret.RRank = e.Trw[1].(float64)
    }
    return ret
}
func (e Entry) String() (ret string) {
    ret = fmt.Sprintln("Input: ", e.Input)
    ret += fmt.Sprintln("Base: ", e.Base)
    ret += fmt.Sprintln("Left: ", e.Tlw)
    ret += fmt.Sprintln("Right: ", e.Trw)
    ret += fmt.Sprintln("Special: ", e.Special)

    return ret
}

var QMKLookup = map[string][]string{
    "!": []string{"KC_LSFT", "KC_1"},
    "'": []string{"KC_QUOT"},
    "(": []string{"KC_LSFT", "KC_9"},
    ")": []string{"KC_LSFT", "KC_0"},
    ",": []string{"KC_COMM"},
    "-": []string{"KC_MINS"},
    ".": []string{"KC_DOT"},
    ";": []string{"KC_SCLN"},
    "?": []string{"KC_QUOT"},
    "a": []string{"KC_A"},
    "b": []string{"KC_B"},
    "c": []string{"KC_C"},
    "d": []string{"KC_D"},
    "e": []string{"KC_E"},
    "f": []string{"KC_F"},
    "g": []string{"KC_G"},
    "h": []string{"KC_H"},
    "i": []string{"KC_I"},
    "j": []string{"KC_J"},
    "k": []string{"KC_K"},
    "l": []string{"KC_L"},
    "m": []string{"KC_M"},
    "n": []string{"KC_N"},
    "o": []string{"KC_O"},
    "p": []string{"KC_P"},
    "q": []string{"KC_Q"},
    "r": []string{"KC_R"},
    "s": []string{"KC_S"},
    "t": []string{"KC_T"},
    "u": []string{"KC_U"},
    "v": []string{"KC_V"},
    "w": []string{"KC_W"},
    "x": []string{"KC_X"},
    "y": []string{"KC_Y"},
    "z": []string{"KC_Z"},

    //specials
    "bksp":  []string{"KC_BSPC"},
    "enter": []string{"KC_ENT"},
    //"numsym":[]string{"NUM)"}, //TODO: Sticky
    //"LETTERS":[]string{"KC_SPC"},

    //symbols
    "[":     []string{"KC_LBRC"},
    "]":     []string{"KC_RBRC"},
    " ":     []string{"KC_SPC"},
    "1":     []string{"KC_1"},
    "2":     []string{"KC_2"},
    "3":     []string{"KC_3"},
    "4":     []string{"KC_4"},
    "5":     []string{"KC_5"},
    "6":     []string{"KC_6"},
    "7":     []string{"KC_7"},
    "8":     []string{"KC_8"},
    "9":     []string{"KC_9"},
    "0":     []string{"KC_0"},
    "=":     []string{"KC_EQL"},
    "Fn":    []string{"KC_NO"},
    "SPACE": []string{"KC_SPC"},
    "Home":  []string{"KC_HOME"},
    "End":   []string{"KC_END"},
    "    ":  []string{"KC_TAB"},
    "   ":   []string{"KC_TAB"},
    "\t":    []string{"KC_TAB"},
    "`":     []string{"KC_GRV"},
}

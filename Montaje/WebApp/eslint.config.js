import js from "@eslint/js";
import stylistic from "@stylistic/eslint-plugin";
import ts from "@typescript-eslint/eslint-plugin";
import parserTs from "@typescript-eslint/parser";
import importPlugin from "eslint-plugin-import";
import eslintPluginSortKeysFix from "eslint-plugin-sort-keys-fix";
import globals from "globals";


export default [
    { ignores: ["dist", "build", "frontend"] },
    {
        files: ["**/*.{js,ts}"],
        languageOptions: {
            globals: globals.node,
            parser: parserTs,
            parserOptions: {
                ecmaVersion: "latest",
                sourceType: "module"
            }
        },
        plugins: {
            "@stylistic": stylistic,
            "@typescript-eslint": ts,
            "importPlugin": importPlugin,
            "sort-keys-fix": eslintPluginSortKeysFix
        },
        rules: {
            ...js.configs.recommended.rules,
            "@stylistic/arrow-spacing": ["error", { "after": true, "before": true }],
            "@stylistic/brace-style": ["error", "1tbs", { "allowSingleLine": true }],
            "@stylistic/comma-dangle": ["error", "never"],
            "@stylistic/comma-spacing": ["error", { "after": true }],
            "@stylistic/eol-last": ["error", "always"],
            "@stylistic/indent": ["error", 4],
            "@stylistic/jsx-quotes": ["error", "prefer-double"],
            "@stylistic/object-curly-spacing": ["error", "always"],
            "@stylistic/quotes": ["error", "double", { "allowTemplateLiterals": "always" }],
            "@stylistic/semi": ["error", "always"],
            "eqeqeq": ["error", "always"],
            "importPlugin/newline-after-import": ["error", { "considerComments": true, "count": 2, "exactCount": true }],
            "importPlugin/order": ["error", {
                "alphabetize": { "caseInsensitive": false, "order": "asc" },
                "groups": [[
                    "index",
                    "type",
                    "object",
                    "external",
                    "internal",
                    "sibling",
                    "parent",
                    "builtin",
                    "unknown"
                ]],
                "named": true,
                "newlines-between": "never"
            }],
            "sort-keys-fix/sort-keys-fix": ["error", "asc", {
                "caseSensitive": true,
                "natural": true
            }]
        }
    }
];

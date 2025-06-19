import React from "react";
import { useState } from "react";


// eslint-disable-next-line no-unused-vars
const useRadio = (name: string, onValueChange: (value: string) => void) => {
    const [value, setValue] = useState<string>("");
    const onChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        setValue(event.target.value);
        onValueChange(event.target.value);
    };
    return {
        setValue,
        value,
        values: {
            name,
            onChange,
            type: "radio"
        }
    };
};

export default useRadio;

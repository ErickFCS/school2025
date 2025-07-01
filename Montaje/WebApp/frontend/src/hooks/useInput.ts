import { ChangeEvent, useState } from "react";


const useInput = (initialValue: string | number, placeHolder: string | number, type: string, name: string, required: boolean) => {
    const [value, setValue] = useState<string | number>(initialValue || "");

    const onChange = (event: ChangeEvent<HTMLInputElement>) => {
        setValue(event.target.value);
    };

    const reset = () => {
        setValue(initialValue || "");
    };

    return {
        reset,
        setValue,
        value,
        values: {
            name,
            onChange,
            placeHolder,
            required,
            type
        }
    };

};

export default useInput;

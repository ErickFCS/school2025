

export const serializeError = (err: any): string => {
    return {
        message: err.message,
        name: err.name,
        stack: err.stack,
        ...err
    };
};
